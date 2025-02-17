Cursor trig_lv;
Cursor offset_lv;
Cursor time_base;

Button min_butt;
Button max_butt;
Button average_butt;
Button pk_pk_butt;

Button display_butt;
Button setings_butt;
Button volt_cursor_butt;
Button gnd_level_butt;
Button time_cursor_butt;

Button single_trigg_butt;
Button norm_trigg_butt;
Button pEdge_butt;
Button nEdge_butt;


Button m100_butt;
Button m200_butt;
Button m500_butt;
Button v1_butt;
Button v2_butt;
Button v5_butt;

//Button ac_butt;
//Button dc_butt;
//Button gnd_butt;

Button volt_measure_butt;

Button time_butt;


Button u1_butt;
Button u2_butt;
Button u5_butt;
Button u10_butt;
Button u20_butt;
Button u50_butt;
Button u100_butt;
Button u200_butt;
Button u500_butt;
Button m1_butt;

Button time_measure_butt;
Button freq_butt;
Button period_butt;

Button persist_butt;
Button line_butt;
Button dot_butt;

//PLASARE BUTOATE 
void butts_place() {
  trig_lv = new Cursor(1090, 307, 1060, 300, 1090, 293);
  offset_lv = new Cursor(10, lat/2+7, 20, lat/2, 10, lat/2-7);
  time_base = new Cursor(10, lat+80, 20, lat+80, 10, lat+80);

  volt_cursor_butt = new Button("Volt Cursor", 1150, 40.0, 100.0, 30.0, 200, 200, 0);
  gnd_level_butt = new Button("GND Seviye", 1150, 90.0, 100.0, 30.0, 200, 200, 0);
  average_butt = new Button("Ortalama", 1150, 140.0, 100.0, 30.0, 200, 200, 0);
  min_butt = new Button("Min", 1150, 190.0, 100.0, 30.0, 200, 200, 0);
  max_butt = new Button("Max", 1150, 240.0, 100.0, 30.0, 200, 200, 0);
  pk_pk_butt = new Button("Pk-Pk", 1150, 290.0, 100.0, 30.0, 200, 200, 0);

  setings_butt = new Button("Ayarlar", 1150, 30.0, 90.0, 30.0, 200, 200, 0);
  display_butt = new Button("Ekran", 1150, 80.0, 90.0, 30.0, 200, 200, 0);

  single_trigg_butt = new Button("Single", 1200.0, 180.0, 80.0, 30.0, 200, 200, 0);
  norm_trigg_butt = new Button("Normal", 1110.0, 180.0, 80.0, 30.0, 200, 200, 0);

  line_butt = new Button("Çizgisel", 1200.0, 190.0, 80.0, 30.0, 200, 200, 0);
  dot_butt = new Button("Noktasal", 1110.0, 190.0, 80.0, 30.0, 200, 200, 0);

  pEdge_butt = new Button("Pos Tetik", 1110.0, 130.0, 80.0, 30.0, 200, 200, 0);
  persist_butt = new Button("Doğrusal", 1150, 140.0, 90.0, 30.0, 200, 200, 0);
  nEdge_butt = new Button("Neg Tetik", 1200.0, 130.0, 80.0, 30.0, 200, 200, 0);

  m100_butt = new Button("100m", 1110.0, 250.0, 80.0, 30.0, 200, 200, 0);
  m200_butt = new Button("200m", 1110.0, 300.0, 80.0, 30.0, 200, 200, 0);
  m500_butt = new Button("500m", 1110.0, 350.0, 80.0, 30.0, 200, 200, 0);
  v1_butt = new Button("1V", 1200.0, 250.0, 80.0, 30.0, 200, 200, 0);
  v2_butt = new Button("2V", 1200.0, 300.0, 80.0, 30.0, 200, 200, 0);
  v5_butt = new Button("5V", 1200.0, 350.0, 80.0, 30.0, 200, 200, 0);

 // ac_butt = new Button("AC", 1110.0, 420.0, 80.0, 30.0, 200, 200, 0);
 // dc_butt = new Button("DC", 1110.0, 470.0, 80.0, 30.0, 200, 200, 0);
  //gnd_butt = new Button("GND", 1110.0, 520.0, 80.0, 30.0, 200, 200, 0);

  volt_measure_butt = new Button("Y ölçümü", 1150.0, 570.0, 90.0, 30.0, 200, 200, 0);

  time_cursor_butt = new Button("Zaman Cursor", 30.0, 620.0, 110.0, 30.0, 200, 200, 0);
  freq_butt = new Button("Frekans", 150.0, 620.0, 110.0, 30.0, 200, 200, 0);
  period_butt = new Button("Periyot", 270.0, 620.0, 110.0, 30.0, 200, 200, 0);

  u1_butt = new Button("1us", 30.0, 620.0, 50.0, 30.0, 200, 200, 0);
  u2_butt = new Button("2us", 100.0, 620.0, 50.0, 30.0, 200, 200, 0);
  u5_butt = new Button("5us", 170.0, 620.0, 50.0, 30.0, 200, 200, 0);
  u10_butt = new Button("10us", 240.0, 620.0, 50.0, 30.0, 200, 200, 0);
  u20_butt = new Button("20us", 310.0, 620.0, 50.0, 30.0, 200, 200, 0);
  u50_butt = new Button("50us", 380.0, 620.0, 50.0, 30.0, 200, 200, 0);
  u100_butt = new Button("100us", 450.0, 620.0, 50.0, 30.0, 200, 200, 0);
  u200_butt = new Button("200us", 520.0, 620.0, 50.0, 30.0, 200, 200, 0);
  u500_butt = new Button("500us", 590.0, 620.0, 50.0, 30.0, 200, 200, 0);
  m1_butt = new Button("1ms", 660.0, 620.0, 50.0, 30.0, 200, 200, 0);

  time_measure_butt = new Button("X Ölçümü", 1010.0, 620.0, 90.0, 30.0, 200, 200, 0);
}

//AFISARE MENIU PRINCIPAL
void display_main_right_butt() {

  display_butt.place();
  single_trigg_butt.place();
  norm_trigg_butt.place();
  pEdge_butt.place();
  nEdge_butt.place();

  m100_butt.place();
  m200_butt.place();
  m500_butt.place();
  v1_butt.place();
  v2_butt.place();
  v5_butt.place();

  //ac_butt.place();
 // dc_butt.place();
 // gnd_butt.place();

  volt_measure_butt.place();  
  setings_butt.place();
  trig_lv.place();
  offset_lv.place();
}

void display_main_bot_butt() {
  u1_butt.place();
  u2_butt.place();
  u5_butt.place();
  u10_butt.place();  
  u20_butt.place();
  u50_butt.place();
  u100_butt.place();
  u200_butt.place();
  u500_butt.place();
  m1_butt.place();
  time_measure_butt.place();
  time_base.place();
}

void display_settings() { 
  trig_lv.place();
  offset_lv.place();
}

void display() {
  persist_butt.place();
  line_butt.place();
  dot_butt.place();
  trig_lv.place();
  offset_lv.place();
  time_base.place();
}

void display_volt_measure() {
  volt_cursor_butt.place();
  gnd_level_butt.place();
  average_butt.place();
  min_butt.place();
  max_butt.place();
  pk_pk_butt.place();
}

void display_time_measure() {

  time_cursor_butt.place();
  freq_butt.place();
  period_butt.place();
}
