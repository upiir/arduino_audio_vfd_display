// VFD (Vacuum Fluorescent Display) module 7-BT-317NK Module FUTABA with Arduino UNO

// created by upir, 2024
// youtube channel: https://www.youtube.com/upir_upir

// YOUTUBE VIDEO: https://youtu.be/out82m-JxXU
// Source Files: https://github.com/upiir/arduino_audio_vfd_display

// Links from the video:
// Do you like this video? You can buy me a coffee ☕: https://www.buymeacoffee.com/upir
// Used VFD display module: https://s.click.aliexpress.com/e/_oBOxJH1
// VFD Clock: https://s.click.aliexpress.com/e/_olAEiG3
// Arduino UNO: https://s.click.aliexpress.com/e/_AXDw1h
// Arduino breadboard prototyping shield: https://s.click.aliexpress.com/e/_ApbCwx
// Jumper Wires: https://s.click.aliexpress.com/e/_DF9YbSV
// Transparent VFD Clock: https://s.click.aliexpress.com/e/_DcGebkt

// Related videos:
// VFD clock and character display: https://youtu.be/g7SOxzKatCc
// 3D on the VFD character display: https://youtu.be/IvMauAxWPkQ
// Graphical VFD Display gauges: https://youtu.be/Frq_JP1lalE

// Connections between the display and Arduino UNO:
// DA (data pin) -> pin 5
// CP (clock pin) -> pin 4
// CS (chip select) -> pin 3
// EN (filament enable) -> 5V
// 5V -> 5V
// GND -> GND


#define PT6315_CS_PIN		  3
#define PT6315_CLK_PIN		4
#define PT6315_DATA_PIN		5

#define CMD_4DIG_24SEG		0x00
#define CMD_5DIG_23SEG		0x01
#define CMD_6DIG_22SEG		0x02
#define CMD_7DIG_21SEG		0x03
#define CMD_8DIG_20SEG		0x04
#define CMD_9DIG_19SEG		0x05
#define CMD_10DIG_18SEG		0x06
#define CMD_11DIG_17SEG		0x07
#define CMD_12DIG_16SEG		0x08

#define CMD_WRITE_DATA_TO_DISPLAY_MODE	0x00
#define CMD_WRITE_DATA_TO_LED_PORT		  0x01
#define CMD_READ_KEY_DATA				        0x10

#define CMD_INCREMENT_ADDRESS_MODE		0x00
#define	CMD_FIXED_ADDRESS_MODE			  0x40
#define CMD_ADDRESS_SET               0xC0

#define	CMD_NORMAL_MODE			0x00
#define	CMD_TEST_MODE				0x80

#define CMD_PULSE_WIDTH_1_16			0x00
#define CMD_PULSE_WIDTH_2_16			0x01
#define CMD_PULSE_WIDTH_4_16			0x02
#define CMD_PULSE_WIDTH_10_16			0x03
#define CMD_PULSE_WIDTH_11_16			0x04
#define CMD_PULSE_WIDTH_12_16			0x05
#define CMD_PULSE_WIDTH_13_16			0x06
#define CMD_PULSE_WIDTH_14_16			0x07

#define CMD_DISPLAY_OFF					0x00
#define	CMD_DISPLAY_ON					0x08

#define DISPLAY_ICON_REC				  0x02
#define	DISPLAY_ICON_CLOCK				0x04
#define DISPLAY_ICON_3D_ON				0x08
#define DISPLAY_ICON_WIFI_ON			0x10

#define SET_PT6315_CS		  digitalWrite(PT6315_CS_PIN, 1)
#define CLR_PT6315_CS		  digitalWrite(PT6315_CS_PIN, 0)

#define SET_PT6315_CLK		digitalWrite(PT6315_CLK_PIN, 1)
#define CLR_PT6315_CLK		digitalWrite(PT6315_CLK_PIN, 0)

#define SET_PT6315_DATA		digitalWrite(PT6315_DATA_PIN, 1)
#define CLR_PT6315_DATA		digitalWrite(PT6315_DATA_PIN, 0)

static const unsigned char font[][3] = {
	{0x8a,0x88,0x06},//0
	{0x84,0x80,0x08},//1
	{0x82,0x0f,0x06},//2
	{0x82,0x87,0x06},//3
	{0x8d,0x87,0x08},//4
	{0x0a,0x87,0x06},//5
	{0x0a,0x8f,0x06},//6
	{0x82,0x80,0x08},//7
	{0x8a,0x8f,0x06},//8
	{0x8a,0x87,0x06},//9

	{0x8a,0x8f,0x09},//A 10
	{0x8b,0x8f,0x07},//B 11
	{0x0e,0x08,0x0e},//C 12
	{0x87,0x88,0x07},//D 13
	{0x0f,0x0f,0x0f},//E 14
	{0x0f,0x0f,0x01},//F 15
	{0x0e,0x8c,0x06},//G 16
	{0x8d,0x8f,0x09},//H 17
	{0x22,0x22,0x06},//I 18
	{0x84,0x88,0x0f},//J 19
	{0x4d,0x4B,0x09},//K 20
	{0x09,0x08,0x0f},//L 21
	{0xdd,0x8a,0x09},//M 22
	{0x9d,0xca,0x09},//N 23
	{0x8f,0x88,0x0f},//O 24
	{0x8b,0x0f,0x01},//P 25
	{0x8a,0xc8,0x06},//Q 26
	{0x8b,0x4f,0x09},//R 27
	{0x0e,0x87,0x07},//S 28
	{0x27,0x22,0x24},//T 29
	{0x8d,0x88,0x8f},//U 30
	{0x95,0xc2,0x08},//V 31
	{0x8d,0xda,0x09},//W 32
	{0x55,0x52,0x09},//X 33
	{0x55,0x22,0x04},//Y 34
	{0x47,0x12,0x0f},//Z 35
	{0xff,0xff,0xff},//全显 36
	{0x00,0x00,0x00}//CLR 37
};

void setup() {
  pinMode(PT6315_CS_PIN, OUTPUT);
  pinMode(PT6315_CLK_PIN, OUTPUT);
  pinMode(PT6315_DATA_PIN, OUTPUT);
  digitalWrite(PT6315_CS_PIN, 1);
  digitalWrite(PT6315_CLK_PIN, 1);
  digitalWrite(PT6315_DATA_PIN, 1);
  delay(200);

  set_vfd_data_mode( CMD_WRITE_DATA_TO_DISPLAY_MODE | CMD_INCREMENT_ADDRESS_MODE | CMD_NORMAL_MODE );
  set_vfd_display_mode(CMD_ADDRESS_SET);
  set_vfd_display_mode(CMD_7DIG_21SEG);
  set_vfd_brightness_on_off(0x0F);
  vfd_clear();
  delay(1);
}

void loop() {


// I LOVE
// character 0
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 0 * 3 ); // position
pt6315_write_byte(B00100010); // segments 7 - 0
pt6315_write_byte(B00100010); // segments 15 - 8
pt6315_write_byte(B00000110); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 1
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 1 * 3 ); // position
pt6315_write_byte(B00000000); // segments 7 - 0
pt6315_write_byte(B00000000); // segments 15 - 8
pt6315_write_byte(B00000000); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 2
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 2 * 3 ); // position
pt6315_write_byte(B00001001); // segments 7 - 0
pt6315_write_byte(B00001000); // segments 15 - 8
pt6315_write_byte(B00001111); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 3
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 3 * 3 ); // position
pt6315_write_byte(B10001010); // segments 7 - 0
pt6315_write_byte(B10001000); // segments 15 - 8
pt6315_write_byte(B00000110); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 4
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 4 * 3 ); // position
pt6315_write_byte(B10010101); // segments 7 - 0
pt6315_write_byte(B11000010); // segments 15 - 8
pt6315_write_byte(B00001000); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 5
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 5 * 3 ); // position
pt6315_write_byte(B00001111); // segments 7 - 0
pt6315_write_byte(B00001111); // segments 15 - 8
pt6315_write_byte(B00001111); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// icon on the left side + red icons on the right side
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 6 * 3 ); // position
pt6315_write_byte(B11111110); // segments 7 - 0
pt6315_write_byte(B00000011); // red icons + segment 8
pt6315_write_byte(B00000000); // unused bits
SET_PT6315_CS; // toggle chip select pin

delay(700);

// VFDS
// character 0
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 0 * 3 ); // position
pt6315_write_byte(B00000000); // segments 7 - 0
pt6315_write_byte(B00000101); // segments 15 - 8
pt6315_write_byte(B00000000); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 1
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 1 * 3 ); // position
pt6315_write_byte(B10010101); // segments 7 - 0
pt6315_write_byte(B11000010); // segments 15 - 8
pt6315_write_byte(B00001000); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 2
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 2 * 3 ); // position
pt6315_write_byte(B00001011); // segments 7 - 0
pt6315_write_byte(B00001011); // segments 15 - 8
pt6315_write_byte(B00000001); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 3
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 3 * 3 ); // position
pt6315_write_byte(B10001011); // segments 7 - 0
pt6315_write_byte(B10001000); // segments 15 - 8
pt6315_write_byte(B00000111); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 4
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 4 * 3 ); // position
pt6315_write_byte(B00001110); // segments 7 - 0
pt6315_write_byte(B10000111); // segments 15 - 8
pt6315_write_byte(B00000111); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 5
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 5 * 3 ); // position
pt6315_write_byte(B00000000); // segments 7 - 0
pt6315_write_byte(B00000101); // segments 15 - 8
pt6315_write_byte(B00000000); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// icon on the left side + red icons on the right side
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 6 * 3 ); // position
pt6315_write_byte(B11100000); // segments 7 - 0
pt6315_write_byte(B00000101); // red icons + segment 8
pt6315_write_byte(B00000000); // unused bits
SET_PT6315_CS; // toggle chip select pin

delay(700);

// HELLO
// character 0
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 0 * 3 ); // position
pt6315_write_byte(B10001101); // segments 7 - 0
pt6315_write_byte(B10001111); // segments 15 - 8
pt6315_write_byte(B00001001); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 1
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 1 * 3 ); // position
pt6315_write_byte(B00001111); // segments 7 - 0
pt6315_write_byte(B00001011); // segments 15 - 8
pt6315_write_byte(B00001111); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 2
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 2 * 3 ); // position
pt6315_write_byte(B00001001); // segments 7 - 0
pt6315_write_byte(B00001000); // segments 15 - 8
pt6315_write_byte(B00001111); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 3
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 3 * 3 ); // position
pt6315_write_byte(B00001001); // segments 7 - 0
pt6315_write_byte(B00001000); // segments 15 - 8
pt6315_write_byte(B00001111); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 4
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 4 * 3 ); // position
pt6315_write_byte(B10001010); // segments 7 - 0
pt6315_write_byte(B10001000); // segments 15 - 8
pt6315_write_byte(B00000110); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 5
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 5 * 3 ); // position
pt6315_write_byte(B00000000); // segments 7 - 0
pt6315_write_byte(B00000111); // segments 15 - 8
pt6315_write_byte(B00000000); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// icon on the left side + red icons on the right side
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 6 * 3 ); // position
pt6315_write_byte(B11011000); // segments 7 - 0
pt6315_write_byte(B00001000); // red icons + segment 8
pt6315_write_byte(B00000000); // unused bits
SET_PT6315_CS; // toggle chip select pin

delay(700);

// WORLD
// character 0
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 0 * 3 ); // position
pt6315_write_byte(B10001101); // segments 7 - 0
pt6315_write_byte(B11011010); // segments 15 - 8
pt6315_write_byte(B00001001); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 1
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 1 * 3 ); // position
pt6315_write_byte(B10001010); // segments 7 - 0
pt6315_write_byte(B10001000); // segments 15 - 8
pt6315_write_byte(B00000110); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 2
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 2 * 3 ); // position
pt6315_write_byte(B10001111); // segments 7 - 0
pt6315_write_byte(B01001111); // segments 15 - 8
pt6315_write_byte(B00001001); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 3
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 3 * 3 ); // position
pt6315_write_byte(B00001001); // segments 7 - 0
pt6315_write_byte(B00001000); // segments 15 - 8
pt6315_write_byte(B00001111); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 4
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 4 * 3 ); // position
pt6315_write_byte(B10001011); // segments 7 - 0
pt6315_write_byte(B10001000); // segments 15 - 8
pt6315_write_byte(B00000111); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 5
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 5 * 3 ); // position
pt6315_write_byte(B10000100); // segments 7 - 0
pt6315_write_byte(B00000000); // segments 15 - 8
pt6315_write_byte(B00001000); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// icon on the left side + red icons on the right side
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 6 * 3 ); // position
pt6315_write_byte(B10110101); // segments 7 - 0
pt6315_write_byte(B00010000); // red icons + segment 8
pt6315_write_byte(B00000000); // unused bits
SET_PT6315_CS; // toggle chip select pin


delay(700);

// ALL LIT
// character 0
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 0 * 3 ); // position
pt6315_write_byte(B11111111); // segments 7 - 0
pt6315_write_byte(B11111111); // segments 15 - 8
pt6315_write_byte(B00001111); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 1
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 1 * 3 ); // position
pt6315_write_byte(B11111111); // segments 7 - 0
pt6315_write_byte(B11111111); // segments 15 - 8
pt6315_write_byte(B00011111); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 2
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 2 * 3 ); // position
pt6315_write_byte(B11111111); // segments 7 - 0
pt6315_write_byte(B11111111); // segments 15 - 8
pt6315_write_byte(B00001111); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 3
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 3 * 3 ); // position
pt6315_write_byte(B11111111); // segments 7 - 0
pt6315_write_byte(B11111111); // segments 15 - 8
pt6315_write_byte(B00011111); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 4
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 4 * 3 ); // position
pt6315_write_byte(B11111111); // segments 7 - 0
pt6315_write_byte(B11111111); // segments 15 - 8
pt6315_write_byte(B00011111); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 5
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 5 * 3 ); // position
pt6315_write_byte(B11111111); // segments 7 - 0
pt6315_write_byte(B11111111); // segments 15 - 8
pt6315_write_byte(B00001111); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// icon on the left side + red icons on the right side
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 6 * 3 ); // position
pt6315_write_byte(B11111111); // segments 7 - 0
pt6315_write_byte(B00011111); // red icons + segment 8
pt6315_write_byte(B00000000); // unused bits
SET_PT6315_CS; // toggle chip select pin


delay(700);

// 1-6
// character 0
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 0 * 3 ); // position
pt6315_write_byte(B10000100); // segments 7 - 0
pt6315_write_byte(B10000000); // segments 15 - 8
pt6315_write_byte(B00001000); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 1
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 1 * 3 ); // position
pt6315_write_byte(B10000011); // segments 7 - 0
pt6315_write_byte(B00010110); // segments 15 - 8
pt6315_write_byte(B00011111); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 2
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 2 * 3 ); // position
pt6315_write_byte(B01000011); // segments 7 - 0
pt6315_write_byte(B01000011); // segments 15 - 8
pt6315_write_byte(B00000110); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 3
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 3 * 3 ); // position
pt6315_write_byte(B10010101); // segments 7 - 0
pt6315_write_byte(B10000110); // segments 15 - 8
pt6315_write_byte(B00011000); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 4
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 4 * 3 ); // position
pt6315_write_byte(B00010110); // segments 7 - 0
pt6315_write_byte(B10000111); // segments 15 - 8
pt6315_write_byte(B00000111); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 5
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 5 * 3 ); // position
pt6315_write_byte(B00001110); // segments 7 - 0
pt6315_write_byte(B01001011); // segments 15 - 8
pt6315_write_byte(B00000111); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// icon on the left side + red icons on the right side
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 6 * 3 ); // position
pt6315_write_byte(B10110101); // segments 7 - 0
pt6315_write_byte(B00010000); // red icons + segment 8
pt6315_write_byte(B00000000); // unused bits
SET_PT6315_CS; // toggle chip select pin


delay(700);

// 7-0
// character 0
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 0 * 3 ); // position
pt6315_write_byte(B01000010); // segments 7 - 0
pt6315_write_byte(B00100110); // segments 15 - 8
pt6315_write_byte(B00000100); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 1
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 1 * 3 ); // position
pt6315_write_byte(B10001010); // segments 7 - 0
pt6315_write_byte(B10001111); // segments 15 - 8
pt6315_write_byte(B00010110); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 2
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 2 * 3 ); // position
pt6315_write_byte(B10010110); // segments 7 - 0
pt6315_write_byte(B10000110); // segments 15 - 8
pt6315_write_byte(B00000110); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 3
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 3 * 3 ); // position
pt6315_write_byte(B11001010); // segments 7 - 0
pt6315_write_byte(B10011010); // segments 15 - 8
pt6315_write_byte(B00010110); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 4
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 4 * 3 ); // position
pt6315_write_byte(B01000100); // segments 7 - 0
pt6315_write_byte(B01000100); // segments 15 - 8
pt6315_write_byte(B00001000); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 5
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 5 * 3 ); // position
pt6315_write_byte(B00010001); // segments 7 - 0
pt6315_write_byte(B00010001); // segments 15 - 8
pt6315_write_byte(B00000001); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// icon on the left side + red icons on the right side
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 6 * 3 ); // position
pt6315_write_byte(B00000110); // segments 7 - 0
pt6315_write_byte(B00001000); // red icons + segment 8
pt6315_write_byte(B00000000); // unused bits
SET_PT6315_CS; // toggle chip select pin


delay(700);

// smileys
// character 0
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 0 * 3 ); // position
pt6315_write_byte(B01010101); // segments 7 - 0
pt6315_write_byte(B01010010); // segments 15 - 8
pt6315_write_byte(B00001001); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 1
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 1 * 3 ); // position
pt6315_write_byte(B00000101); // segments 7 - 0
pt6315_write_byte(B10001111); // segments 15 - 8
pt6315_write_byte(B00000110); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 2
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 2 * 3 ); // position
pt6315_write_byte(B00000101); // segments 7 - 0
pt6315_write_byte(B10001000); // segments 15 - 8
pt6315_write_byte(B00000110); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 3
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 3 * 3 ); // position
pt6315_write_byte(B01010000); // segments 7 - 0
pt6315_write_byte(B01010000); // segments 15 - 8
pt6315_write_byte(B00000000); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 4
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 4 * 3 ); // position
pt6315_write_byte(B00100101); // segments 7 - 0
pt6315_write_byte(B00000010); // segments 15 - 8
pt6315_write_byte(B00001111); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// character 5
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 5 * 3 ); // position
pt6315_write_byte(B00000101); // segments 7 - 0
pt6315_write_byte(B11000111); // segments 15 - 8
pt6315_write_byte(B00000000); // 3 unused bits + seg. 20 - 16
SET_PT6315_CS; // toggle chip select pin
// icon on the left side + red icons on the right side
CLR_PT6315_CS; // toggle chip select pin
pt6315_write_byte( 0xC0 | 6 * 3 ); // position
pt6315_write_byte(B11000110); // segments 7 - 0
pt6315_write_byte(B00000100); // red icons + segment 8
pt6315_write_byte(B00000000); // unused bits
SET_PT6315_CS; // toggle chip select pin

delay(700);

}

void delay_func(void)
{
	uint8_t i = 5;
	while(i--);
}

void pt6315_write_byte(unsigned char data)
{
	for ( int i = 0; i < 8; i++ )
	{
		CLR_PT6315_CLK;
		if ( data & 0x01 )
		{
			SET_PT6315_DATA;
		}
		else
		{
			CLR_PT6315_DATA;
		}
		data = data >> 1;
		delay_func();
		SET_PT6315_CLK;
		delay_func();
	}
}

void vfd_clear(void)
{
	CLR_PT6315_CS;
	pt6315_write_byte(0xC0);
	for ( int i = 0; i < 21; i++)
	{
		pt6315_write_byte(0x00);
	}
	SET_PT6315_CS;
}

void display_img(unsigned char seg)
{
	CLR_PT6315_CS;
	pt6315_write_byte( 0xC0 | 18 );
	pt6315_write_byte(0xff);
	pt6315_write_byte(0xff);
	pt6315_write_byte(0xff);
	SET_PT6315_CS;
}

void display_char(unsigned char pos, unsigned char data, unsigned char dot)
{
	unsigned char display_buffer[3];
	if ( pos > 5 )
	{
		return ;
	}
	if ( data >= '0' && data <= '9' )
	{
		display_buffer[0] = font[data - '0'][0];
		display_buffer[1] = font[data - '0'][1];
		display_buffer[2] = font[data - '0'][2];
	}
	else if ( data >= 'A' && data <= 'Z' )
	{
		display_buffer[0] = font[data - 'A' + 10][0];
		display_buffer[1] = font[data - 'A' + 10][1];
		display_buffer[2] = font[data - 'A' + 10][2];
	}
	else if(data < '0')
	{
		display_buffer[0] = font[data][0];
		display_buffer[1] = font[data][1];
		display_buffer[2] = font[data][2];
	}
	else
	{
		return;
	}
	if ( ( pos == 1 || pos == 3 || pos == 4 ) && dot )
	{
		display_buffer[2] = display_buffer[2] | 0x10;
	}
	unsigned char temp;
	temp = pos * 3;
	CLR_PT6315_CS;
	pt6315_write_byte( 0xC0 | temp );
	pt6315_write_byte(display_buffer[0]);
	pt6315_write_byte(display_buffer[1]);
	pt6315_write_byte(display_buffer[2]);
	SET_PT6315_CS;
}

void display_icon(unsigned data)
{
	CLR_PT6315_CS;
	pt6315_write_byte(0xD2);
	pt6315_write_byte(0x00);
	pt6315_write_byte(data);
	pt6315_write_byte(0x00);
	SET_PT6315_CS;
}

void set_vfd_display_mode(unsigned char mode)
{
	CLR_PT6315_CS;
	pt6315_write_byte(mode);
	SET_PT6315_CS;
}

void set_vfd_data_mode(unsigned char mode)
{
	CLR_PT6315_CS;
	pt6315_write_byte(0x40 | mode);
	SET_PT6315_CS;
}

void set_vfd_brightness_on_off(unsigned char mode)
{
	CLR_PT6315_CS;
	pt6315_write_byte(0x80 | mode);
	SET_PT6315_CS;
}