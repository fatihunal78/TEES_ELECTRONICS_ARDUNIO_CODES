
void mouseClicked() {


  if (mouseButton == CENTER) {
    offset_lv.move = 0;
    offset = 0;
  }


  if (m1_butt.MouseIsOver() && !time_measure_butt.state) {
    puncte = 256;
    deflex_t = 210;
    m1_butt.state = true;
    u500_butt.state = false;
    u200_butt.state = false;
    u100_butt.state = false;
    u50_butt.state = false;
    u20_butt.state = false;
    u10_butt.state = false;
    u5_butt.state = false;
    u2_butt.state = false;
    u1_butt.state = false;
    port.write("Z");
  }

  if (u500_butt.MouseIsOver() && !time_measure_butt.state) {
    puncte = 256;
    deflex_t = 117;
    m1_butt.state = false;
    u500_butt.state = true;
    u200_butt.state = false;
    u100_butt.state = false;
    u50_butt.state = false;
    u20_butt.state = false;
    u10_butt.state = false;
    u5_butt.state = false;
    u2_butt.state = false;
    u1_butt.state = false;
    port.write("X");
  }

  if (u200_butt.MouseIsOver() && !time_measure_butt.state) {
    puncte = 128;
    deflex_t = 115;
    m1_butt.state = false;
    u500_butt.state = false;
    u200_butt.state = true;
    u100_butt.state = false;
    u50_butt.state = false;
    u20_butt.state = false;
    u10_butt.state = false;
    u5_butt.state = false;
    u2_butt.state = false;
    u1_butt.state = false;
    port.write("X");
  }

  if (u100_butt.MouseIsOver() && !time_measure_butt.state) {
    puncte = 64;
    deflex_t = 114;
    m1_butt.state = false;
    u500_butt.state = false;
    u200_butt.state = false;
    u100_butt.state = true;
    u50_butt.state = false;
    u20_butt.state = false;
    u10_butt.state = false;
    u5_butt.state = false;
    u2_butt.state = false;
    u1_butt.state = false;
    port.write("X");
  }

  if (u50_butt.MouseIsOver() && !time_measure_butt.state) {
    puncte = 256;
    deflex_t = 62;
    m1_butt.state = false;
    u500_butt.state = false;
    u200_butt.state = false;
    u100_butt.state = false;
    u50_butt.state = true;
    u20_butt.state = false;
    u10_butt.state = false;
    u5_butt.state = false;
    u2_butt.state = false;
    u1_butt.state = false;
    port.write("C");
  }

  if (u20_butt.MouseIsOver()&& !time_measure_butt.state) {
    puncte = 128;
    deflex_t = 62;
    m1_butt.state = false;
    u500_butt.state = false;
    u200_butt.state = false;
    u100_butt.state = false;
    u50_butt.state = false;
    u20_butt.state = true;
    u10_butt.state = false;
    u5_butt.state = false;
    u2_butt.state = false;
    u1_butt.state = false;
    port.write("C");
  }

  if (u10_butt.MouseIsOver()&& !time_measure_butt.state) {
    puncte = 64;
    deflex_t = 63;
    m1_butt.state = false;
    u500_butt.state = false;
    u200_butt.state = false;
    u100_butt.state = false;
    u50_butt.state = false;
    u20_butt.state = false;
    u10_butt.state = true;
    u5_butt.state = false;
    u2_butt.state = false;
    u1_butt.state = false;
    port.write("C");
  }
  if (u5_butt.MouseIsOver() && !time_measure_butt.state) {
    puncte = 256;
    deflex_t = 35;
    m1_butt.state = false;
    u500_butt.state = false;
    u200_butt.state = false;
    u100_butt.state = false;
    u50_butt.state = false;
    u20_butt.state = false;
    u10_butt.state = false;
    u5_butt.state = true;
    u2_butt.state = false;
    u1_butt.state = false;
    port.write("V");
  }
  if (u2_butt.MouseIsOver()&& !time_measure_butt.state) {
    puncte = 128;
    deflex_t = 35;
    m1_butt.state = false;
    u500_butt.state = false;
    u200_butt.state = false;
    u100_butt.state = false;
    u50_butt.state = false;
    u20_butt.state = false;
    u10_butt.state = false;
    u5_butt.state = false;
    u2_butt.state = true;
    u1_butt.state = false;
    port.write("V");
  }
  if (u1_butt.MouseIsOver() && !time_measure_butt.state) {
    puncte = 64;
    deflex_t = 22;
    m1_butt.state = false;
    u500_butt.state = false;
    u200_butt.state = false;
    u100_butt.state = false;
    u50_butt.state = false;
    u20_butt.state = false;
    u10_butt.state = false;
    u5_butt.state = false;
    u2_butt.state = false;
    u1_butt.state = true;
    port.write("B");
  }





  if (!volt_measure_butt.state) {

    if (line_butt.MouseIsOver() && display_butt.state) {
      if (!line_butt.state) {
        line_butt.state = true;
        dot_butt.state = false;
      } else {
        line_butt.state = false;
      }
    }

    if (dot_butt.MouseIsOver() && display_butt.state) {
      if (!dot_butt.state) {
        dot_butt.state = true;
        line_butt.state = false;
      } else {
        dot_butt.state = false;
      }
    }

    if ( setings_butt.state || display_butt.state) {
      busy_menu = true;
    } else {
      busy_menu = false;
    }

    if (persist_butt.MouseIsOver() && display_butt.state) {
      if ( !persist_butt.state ) {
        persist_butt.state = true;
      } else {
        persist_butt.state = false;
      }
    }

    if (setings_butt.MouseIsOver()) {
      if ( !setings_butt.state ) {
        setings_butt.state = true;
        display_main_right_butt();
        noStroke();
        fill(0, 100, 150);
        rect(lung + 3, 70, width -lung, 550);
      } else {
        noStroke();
        fill(0, 100, 150);
        rect(lung + 3, 120, width -lung, 450);
        setings_butt.state = false;
        display_main_right_butt();
      }
    }

    if (display_butt.MouseIsOver() &&(!setings_butt.state )) {
      if (display_butt.state == false) {
        display_butt.state = true;
        display_main_right_butt();
        noStroke();
        fill(0, 100, 150);
        rect(lung + 3, 120, width -lung, 500);
      } else {
        noStroke();
        fill(0, 100, 150);
        rect(lung + 3, 120, width -lung, 500);
        display_butt.state = false;
        display_main_right_butt();
      }
    }




    //if (ac_butt.MouseIsOver() &&(!busy_menu)) {
    //  port.write("a");
    //  ac_butt.state = true;
    //  dc_butt.state = false;
    //  gnd_butt.state = false;
    //}


    //if (dc_butt.MouseIsOver() &&(!busy_menu)) {
    //  port.write("A");
    //  dc_butt.state = true;
    //  ac_butt.state = false;
    //  gnd_butt.state = false;
    //}

    //if (gnd_butt.MouseIsOver() &&(!busy_menu)) {
    //  port.write("G");
    //  port.write("R");
    //  pEdge_butt.state = false;
    //  gnd_butt.state = true;
    //  ac_butt.state = false;
    //  dc_butt.state = false;
    //}

    if (m100_butt.MouseIsOver() &&(!busy_menu)) {
      deflexie = -1000;
      m100_butt.state = true;
      m200_butt.state = false;
      m500_butt.state = false;
      v1_butt.state = false;
      v2_butt.state = false;
      v5_butt.state = false;
      port.write("U");// => VREF 1V1
    }

    if (m200_butt.MouseIsOver() &&(!busy_menu)) {
      deflexie = -800;
      m100_butt.state = false;
      m200_butt.state = true;
      m500_butt.state = false;
      v1_butt.state = false;
      v2_butt.state = false;
      v5_butt.state = false;
      port.write("U");// => VREF 2V56
    }

    if (m500_butt.MouseIsOver() &&(!busy_menu)) {
      deflexie = -425;
      m100_butt.state = false;
      m200_butt.state = false;
      m500_butt.state = true;
      v1_butt.state = false;
      v2_butt.state = false;
      v5_butt.state = false;
      port.write("Y");// => VREF 5V
    }

    if (v1_butt.MouseIsOver() &&(!busy_menu)) {
      deflexie = -60;
      m100_butt.state = false;
      m200_butt.state = false;
      m500_butt.state = false;
      v1_butt.state = true;
      v2_butt.state = false;
      v5_butt.state = false;
      port.write("Y");// => VREF 5V
    }

    if (v2_butt.MouseIsOver() &&(!busy_menu)) {
      deflexie = lat/2 - 190;
      m100_butt.state = false;
      m200_butt.state = false;
      m500_butt.state = false;
      v1_butt.state = false;
      v2_butt.state = true;
      v5_butt.state = false;
      port.write("Y");// => VREF 5V
    }

    if (v5_butt.MouseIsOver() &&(!busy_menu)) {
      deflexie = lat/2 - 75;
      m100_butt.state = false;
      m200_butt.state = false;
      m500_butt.state = false;
      v1_butt.state = false;
      v2_butt.state = false;
      v5_butt.state = true;
      port.write("Y");// => VREF 5V
    }

    if (pEdge_butt.MouseIsOver() &&(!busy_menu)) {
      port.write("T");
      pEdge_butt.state = true;
      nEdge_butt.state = false;
    }

    if (nEdge_butt.MouseIsOver() &&(!busy_menu)) {
      port.write("t");
      nEdge_butt.state = true;
      pEdge_butt.state = false;
    }

    if (single_trigg_butt.MouseIsOver() &&(!busy_menu)) {
      port.write("S");
      single_trigg_butt.state = true;
      norm_trigg_butt.state = false;
    }

    if (norm_trigg_butt.MouseIsOver() && (!busy_menu)) {
      port.write("R");
      norm_trigg_butt.state = true;
      single_trigg_butt.state = false;
    }
  }

  if (volt_measure_butt.MouseIsOver()) {
    if (!volt_measure_butt.state) {
      volt_measure_butt.state = true;
      display_main_right_butt();
      noStroke();
      fill(0, 100, 150);
      rect(lung + 3, 0, 200, 560);
    } else {
      volt_measure_butt.state = false;       
      noStroke();
      fill(0, 100, 150);
      rect(lung + 3, 0, 200, 560);
      display_main_right_butt();
    }
  }


  if (volt_cursor_butt.MouseIsOver() && volt_measure_butt.state) {
    if (!volt_cursor_butt.state) {
      volt_cursor_butt.state= true;
    } else {
      volt_cursor_butt.state = false;
    }
  }


  if (gnd_level_butt.MouseIsOver() && volt_measure_butt.state) {
    if (!gnd_level_butt.state) {
      gnd_level_butt.state= true;
    } else {
      gnd_level_butt.state = false;
    }
  }

  if (average_butt.MouseIsOver() && volt_measure_butt.state) {
    if (!average_butt.state) {
      average_butt.state= true;
    } else {
      average_butt.state = false;
    }
  }


  if (min_butt.MouseIsOver() && volt_measure_butt.state) {
    if (!min_butt.state) {
      min_butt.state= true;
    } else {
      min_butt.state = false;
    }
  }


  if (max_butt.MouseIsOver() && volt_measure_butt.state) {
    if (!max_butt.state) {
      max_butt.state= true;
    } else {
      max_butt.state = false;
    }
  }

  if (pk_pk_butt.MouseIsOver() && volt_measure_butt.state) {
    if (!pk_pk_butt.state) {
      pk_pk_butt.state= true;
    } else {
      pk_pk_butt.state = false;
    }
  }


  if (time_measure_butt.MouseIsOver()) {
    if (!time_measure_butt.state) {
      time_measure_butt.state = true;
      display_main_bot_butt();
      noStroke();
      fill(0, 100, 150);
      rect(0, 610, 800, 100);
    } else {
      time_measure_butt.state = false;
      noStroke();
      fill(0, 100, 150);
      rect(0, 610, 800, 100);
      display_main_bot_butt();
    }
  }

  if (time_cursor_butt.MouseIsOver() && time_measure_butt.state) {
    if (!time_cursor_butt.state) {
      time_cursor_butt.state = true;
    } else {
      time_cursor_butt.state =false;
    }
  }
}



void mouseReleased() {

  over_cursor_volt_1 = false;
  over_cursor_volt_2 = false;
  over_cursor_time_1 = false;
  over_cursor_time_2 = false;
  over_trig_lv = false;
}




void mousePressed() {

  if ( mouseY >= (trig_lv.y_2+trig_lv.move) - 5 && mouseY <= (trig_lv.y_2 +trig_lv.move) + 10 && mouseX >= 950 && mouseX <=1100) {
    over_trig_lv = true;
  }

  if (mouseY >= cursor_volt_1 - 5 &&  mouseY <= cursor_volt_1 + 5) {
    over_cursor_volt_1 = true;
  }

  if (mouseY >= cursor_volt_2 - 5 &&  mouseY <= cursor_volt_2 + 5) {
    over_cursor_volt_2 = true;
  }

  if (mouseX >= cursor_time_1 - 5 &&  mouseX <= cursor_time_1 + 5) {
    over_cursor_time_1 = true;
  }

  if (mouseX >= cursor_time_2 - 5 &&  mouseX <= cursor_time_2 + 5) {
    over_cursor_time_2 = true;
  }
}

void mouseWheel(MouseEvent event) {

  float e = event.getCount();

  if (offset > - 295 && offset < 295) {
    if (e>0) {
      offset -=5;
    }
    if (e<0) {
      offset +=5;
    }
    offset_lv.move = -offset;
  }
}


void mouseDragged() {
  if (mouseY < lat) {
    if (over_cursor_volt_1) {
      cursor_volt_1 = mouseY;
    }
    if (over_cursor_volt_2) {
      cursor_volt_2 = mouseY;
    }
  }

  if (mouseX < lung) {
    if (over_cursor_time_1) {
      cursor_time_1 = mouseX;
    }
    if (over_cursor_time_2) {
      cursor_time_2 = mouseX;
    }
  }

  if (mouseX < lung) {
    if (over_trig_lv) {
      trig_lv.move = parseInt(map(mouseY, 0, 600, -300, 300));
      trig_pos = parseInt(map(mouseY, 0, 600, 1024, 0));

      // port.write("P"+trig_pos);
    }
  }
}
