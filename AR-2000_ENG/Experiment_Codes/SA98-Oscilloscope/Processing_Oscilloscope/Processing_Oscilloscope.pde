import processing.serial.*;
PFont f;

void setup() {
  size(1300, 700);
  
  f = createFont("Arial", 0.5, true);
  background();
  butts_place();
  display_main_right_butt();
  display_main_bot_butt();

 
  norm_trigg_butt.state = true;
  pEdge_butt.state = true;
  v2_butt.state = true;
  //dc_butt.state = true;
  u500_butt.state = true;
  line_butt.state = true;

  
  while (state) {
    try {
      choosePort();
      port = new Serial(this, serial_bun, 115200);
      port.bufferUntil('\n');
      state = false;
    }
    catch(Exception e) {
      err_window();
      // println("Nu exista port");
      state = true;
    }
  }

  fill(250, 250, 0);
  textSize(18);
  textAlign(LEFT);
  text("TEES ELEKTRONİK", 1100, 670);
  text("ARDUINO OSİLOSKOP", 1100, 690);
}

void draw() {

  if (RX) {
    signal();
  }

  if (time_measure_butt.state) {
    display_time_measure();
  } else {
    display_main_bot_butt();
  }

  if (setings_butt.state) {
    display_settings();
  } else if (display_butt.state) {
    display();
  } else if (volt_measure_butt.state) {
    display_volt_measure();
  } else {
    display_main_right_butt();
  }
}



void background() {

  background(0, 100, 150);
  fill(0);
  rect(0, 0, lung, lat);

  //linii INITIAL
  stroke(130);
  strokeWeight(1);
  for (int l = 0; l <= lung; l = l + lung/10) {

    line(l, 0, l, lat );
  }
  for (int l = 0; l <= lat; l = l + lat/8) {
    line(0, l, lung, l );
  }

  //rama la fereastra INITIAL
  noFill();
  stroke(200);
  strokeWeight(5);
  rect(0, 0, lung, lat, 5);
}

//FUNCTIA DE REFRESH A GRAFICULUI
void refresh() {
  fill(0);
  rect(0, 0, lung, lat);

  //linii DIN NOU
  stroke(130);
  strokeWeight(1);
  for (int l = 0; l <= lung; l = l + lung/10) {

    line(l, 0, l, lat );
  }
  for (int l = 0; l <= lat; l = l + lat/8) {
    line(0, l, lung, l );
  }

  //rama la fereastra DIN NOU
  noFill();
  stroke(200);
  strokeWeight(5);
  rect(0, 0, lung, lat, 5);

  //INDICATORI
  trig_lv.place();
  offset_lv.place();
  time_base.place();

  //LINII DE CURSORI + TEXTUL AFERENT
  if (volt_cursor_butt.state) {
    stroke(250, 250, 0);
    strokeWeight(2);
    line(5, cursor_volt_1, lung-5, cursor_volt_1);
    line(5, cursor_volt_2, lung-5, cursor_volt_2);
    cursor_volt_lv1 = parseInt(map(cursor_volt_1, 0, lat, deflexie*70.5, -deflexie*70.5));
    cursor_volt_lv2 = parseInt(map(cursor_volt_2, 0, lat, deflexie*70.5, -deflexie*70.5));
    text("Cursor 1: " + cursor_volt_lv1 + "mV", 1020, 30);
    text("Cursor 2: " + cursor_volt_lv2 + "mV", 1020, 50);
    text("ΔV: " + abs(cursor_volt_lv1 - cursor_volt_lv2) + "mV", 1020, 70);
  }

  if (time_cursor_butt.state) {
    stroke(250, 180, 0);
    strokeWeight(2);
    line(cursor_time_1, 3, cursor_time_1, lat-3);
    line(cursor_time_2, 3, cursor_time_2, lat-3);
    cursor_time_lv1 = parseInt(map(cursor_time_1, 0, lung, 0, deflex_t*puncte));
    cursor_time_lv2 = parseInt(map(cursor_time_2, 0, lung, 0, deflex_t*puncte));
    text("Cursor 1: " + cursor_time_lv1 + "us", 1020, 530);
    text("Cursor 2: " + cursor_time_lv2 + "us", 1020, 550);
    text("Δt: " + abs(cursor_time_lv1 - cursor_time_lv2) + "us", 1020, 570);
    text("Freq: " + nf(1000000/abs(cursor_time_lv2 - cursor_time_lv1), 0, 2) + "Hz", 1020, 590);
  }

  if (single_trigg_butt.state) {
    if (single_acq) {
      text("İşlem Tamamlandı", 550, 30);
    } 
    if (!single_acq) {
      text("Bekleniyor...", 550, 30);
    }
  }

  //INFORMATII MASURATORI
  if (gnd_level_butt.state) {
    gnd_lv =map(offset, 0, 370, 0, 5);
    text("GND Level: " + nf(gnd_lv, 0, 2) + "V", 80, 580);
  }
  if (RX) {
    if (average_butt.state) {
      average = map(average, 0, 1023, 0, 4.95);
      text("Average: " + nf(average, 0, 2) + "V", 80, 30);
      delay(50);
    }
    if (min_butt.state) {
      min_volt = map(min_volt, 0, 1023, 0, 4.95);
      text("Min: " + nf(min_volt, 0, 2) + "V", 80, 50);
      delay(50);
    }
    if (max_butt.state) {
      max_volt = map(max_volt, 0, 1023, 0, 4.95);
      text("Max: " + nf(max_volt, 0, 2) + "V", 80, 70);
      delay(50);
    }
    if (pk_pk_butt.state) {  
      peak_to_peak = map(peak_to_peak, 0, 1023, 0, 4.95);
      text("Pk-Pk: " + nf(peak_to_peak, 0, 2) + "V", 80, 90);
    }
  }
  text("Triger Level: " + nf(map(trig_pos, 0, 1023, 0, 4.95), 0, 2) +"V", 860, 590);
}

//ALEGERAE PORTULUI DE COMM
void choosePort() {


  usb = Serial.list();
  for (i = 0; i < usb.length; i++) {

    if (usb[i] != null) {
      serial_bun = usb[i];
    }
  }
}
