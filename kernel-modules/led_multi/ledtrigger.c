#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/leds.h>
#include <linux/slab.h>
#include <linux/timer.h>

// 自定义触发器核心结构体
static struct led_trigger *multifunc_trigger;
static struct timer_list custom_blink_timer;
static int current_mode = 0; // 0:心跳, 1:闪烁, 2:常亮

// 定时器回调函数（负责底层高精度控灯）
static void led_multifunc_timer_func(struct timer_list *t)
{
    struct led_classdev *led_cdev;
    static bool on = false;

    // 锁死触发器链表，遍历当前所有绑定了该触发器的 LED 灯
    read_lock(&multifunc_trigger->leddev_list_lock);
    list_for_each_entry(led_cdev, &multifunc_trigger->leddev_list, trig_list) {
        if (current_mode == 2) {
            led_set_brightness(led_cdev, LED_FULL); // 紧急状态：强行常亮
        } else if (current_mode == 1) {
            led_set_brightness(led_cdev, on ? LED_FULL : LED_OFF); // 闪烁模式
        } else {
            // 默认模式（比如心跳，这里可以用内核标准的 heartbeat 逻辑）
        }
    }
    read_unlock(&multifunc_trigger->leddev_list_lock);

    on = !on;
    // 周期性循环定时器（每 200 毫秒迭代一次）
    mod_timer(&custom_blink_timer, jiffies + msecs_to_jiffies(200));
}

// 模块初始化
static int __init led_multifunc_trig_init(void)
{
    // 1. 动态注册一个名为 "led-smart-audio" 的全新内核触发器
    led_trigger_register_simple("led-smart-audio", &multifunc_trigger);
    
    // 2. 初始化内核硬定时器
    timer_setup(&custom_blink_timer, led_multifunc_timer_func, 0);
    mod_timer(&custom_blink_timer, jiffies + msecs_to_jiffies(200));

    pr_info("智能音箱多功能 LED 触发器驱动已成功加载\n");
    return 0;
}

// 模块卸载
static void __exit led_multifunc_trig_exit(void)
{
    del_timer_sync(&custom_blink_timer);
    led_trigger_unregister(multifunc_trigger);
    pr_info("多功能 LED 触发器驱动已卸载\n");
}

// 导出内核 API，允许音箱的其他驱动（如音频、网络、陀螺仪）直接调用修改当前模式
void set_led_multifunc_mode(int mode) {
    current_mode = mode;
}
EXPORT_SYMBOL_GPL(set_led_multifunc_mode);

module_init(led_multifunc_trig_init);
module_exit(led_multifunc_trig_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Smart Speaker Multi-function LED Trigger");
