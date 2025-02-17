//SERIAL + VECTOR DE SAMPLE-URI
String data;
float value;
Serial port;
String[] usb;
String serial_bun;

int puncte = 256;
int dim = 512;
float vector[]= new float[dim];
int ch;
float rezolution;
float pas_horiz;

float values[] = new float[512];

String samples[];
String coding[];



//FEREASTRA PRINCIPALA + AFISARI
final int lung = 1100;
final int lat = 600;
float gnd_lv;
float deflexie = lat/2 - 190;
float deflex_t = 0;
int offset = 0;
int trig_pos = 0;


//MASURATORI
float min_volt = 0;
float max_volt = 0;
float peak_to_peak = 0;
float average;
float sum = 0;
int cursor_volt_1 = 200;
int cursor_volt_2 = 400;
int cursor_volt_lv1 = 0;
int cursor_volt_lv2 = 0;


int cursor_time_1 = 100;
int cursor_time_2 = 300;
int cursor_time_lv1 = 0;
int cursor_time_lv2 = 0;

//INDECSI
float index = 0;
int i = 0;
int k, l = 0;


//STARI
boolean RX;
boolean state = true;
boolean persistance = false;
boolean over_cursor_volt_1;
boolean over_cursor_volt_2;
boolean over_cursor_time_1;
boolean over_cursor_time_2;
boolean over_trig_lv;
boolean busy_menu;
boolean single_acq = false;
