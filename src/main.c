#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

 /* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led2" alias. */
#define LED1_NODE DT_ALIAS(led0)
#define LED2_NODE DT_ALIAS(led1)
#define LED3_NODE DT_ALIAS(led3)
#define BTN1 DT_ALIAS(sw0)
#define BTN2 DT_ALIAS(sw1)
#define BTN3 DT_ALIAS(sw2)
#define BTN4 DT_ALIAS(sw3)

#define MAX_KEYPRESS 6
const char* valid = "123123";

typedef struct
{
        char letter;
        int next;
} node;
node* next = NULL;
node* first = NULL;
int tries = 0;

node array[MAX_KEYPRESS];

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET_OR(LED1_NODE, gpios, { 0 });
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET_OR(LED2_NODE, gpios, { 0 });
static const struct gpio_dt_spec led3 = GPIO_DT_SPEC_GET_OR(LED3_NODE, gpios, { 0 });

static const struct gpio_dt_spec btn1 = GPIO_DT_SPEC_GET_OR(BTN1, gpios,
      { 0 });
static const struct gpio_dt_spec btn2 = GPIO_DT_SPEC_GET_OR(BTN2, gpios,
      { 0 });
static const struct gpio_dt_spec btn3 = GPIO_DT_SPEC_GET_OR(BTN3, gpios,
      { 0 });
static const struct gpio_dt_spec btn4 = GPIO_DT_SPEC_GET_OR(BTN4, gpios,
      { 0 });

static struct gpio_callback button_cb_data;
static struct gpio_callback button_cb_data2;
static struct gpio_callback button_cb_data3;
static struct gpio_callback button_cb_data4;

void add_to_combo(char letter)
{
        if (next == NULL)
        {
                next = array;
                next->letter = letter;
                first = next;
        }
        else
        {
                array[next->next].letter = letter;
                next = &array[next->next];
        }
        tries++;

        if (tries > MAX_KEYPRESS)
        {
                tries = 0;
                first = &array[first->next];
        }
}

void clear_combo()
{
        next = NULL;
        first = NULL;
        tries = 0;
}

void flashLed1()
{
        gpio_pin_toggle_dt(&led1);
        k_msleep(200);
        gpio_pin_toggle_dt(&led1);
}

void flashLed2()
{
        for (int i = 0; i < 10; i++)
        {
                gpio_pin_toggle_dt(&led2);
                k_msleep(50);
        }
        gpio_pin_set_dt(&led2, 0);
}

void flashLed3()
{
        gpio_pin_set_dt(&led3, 1);
        k_msleep(3000);
        gpio_pin_set_dt(&led3, 0);
}

bool is_valid()
{
        char compare[MAX_KEYPRESS + 1];
        compare[MAX_KEYPRESS] = '\0';
        node* n = first;
        int j = 0;
        while (n != next)
{
        compare[j] = n->letter;
        j++;
        n = &array[n->next];
        }
        compare[j] = next->letter;

        return (strcmp(compare, valid) == 0);
}

void init()
{
        for (int i = 0; i < MAX_KEYPRESS; i++)
        {
                array[i].letter = '\0';
                array[i].next = i + 1;
        }
        array[MAX_KEYPRESS - 1].next = 0;
}

int main(void)
{
        init();

        int ret;

        if (!gpio_is_ready_dt(&led1)) {
        return 0;
}

        if (!gpio_is_ready_dt(&led2)) {
        return 0;
}

        if (!gpio_is_ready_dt(&led3)) {
        return 0;
}

ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT);
if (ret < 0) {
return 0;
}

ret = gpio_pin_configure_dt(&led2, GPIO_OUTPUT);
if (ret < 0) {
        return 0;
}

ret = gpio_pin_configure_dt(&led3, GPIO_OUTPUT);
if (ret < 0) {
        return 0;
}

if (!gpio_is_ready_dt(&btn1)) {
        return 0;
}

if (!gpio_is_ready_dt(&btn2)) {
        return 0;
}

if (!gpio_is_ready_dt(&btn3)) {
        return 0;
}

if (!gpio_is_ready_dt(&btn4)) {
        return 0;
}

ret = gpio_pin_configure_dt(&btn1, GPIO_INPUT);
if (ret != 0) {
        return 0;
}

ret = gpio_pin_configure_dt(&btn2, GPIO_INPUT);
if (ret != 0) {
        return 0;
}

ret = gpio_pin_configure_dt(&btn3, GPIO_INPUT);
if (ret != 0) {
        return 0;
}

ret = gpio_pin_configure_dt(&btn4, GPIO_INPUT);
if (ret != 0) {
        return 0;
}

ret = gpio_pin_interrupt_configure_dt(&btn1,GPIO_INT_EDGE_TO_ACTIVE);
if (ret != 0) {
        return 0;
}

ret = gpio_pin_interrupt_configure_dt(&btn2,GPIO_INT_EDGE_TO_ACTIVE);
if (ret != 0) {
        return 0;
}

ret = gpio_pin_interrupt_configure_dt(&btn3,GPIO_INT_EDGE_TO_ACTIVE);
if (ret != 0) {
        return 0;
}

ret = gpio_pin_interrupt_configure_dt(&btn4,GPIO_INT_EDGE_TO_ACTIVE);
if (ret != 0) {
        return 0;
}

gpio_pin_set_dt(&led1, 0);
gpio_pin_set_dt(&led2, 0);
gpio_pin_set_dt(&led3, 0);
while (1)
{
        if (gpio_pin_get_dt(&btn1) || gpio_pin_get_dt(&btn2) || gpio_pin_get_dt(&btn3))
        {
                flashLed1();
                if (gpio_pin_get_dt(&btn1))
                {
                        add_to_combo('1');
                }
                else if (gpio_pin_get_dt(&btn2))
                {
                        add_to_combo('2');
                }
                else if (gpio_pin_get_dt(&btn3))
                {
                        add_to_combo('3');
                }
        }
        else if (gpio_pin_get_dt(&btn4))
        {
        if (is_valid())
        {
                flashLed3();
        }
        else
        {
                flashLed2();
        }
        clear_combo();
        }
}

        return 0;
}
