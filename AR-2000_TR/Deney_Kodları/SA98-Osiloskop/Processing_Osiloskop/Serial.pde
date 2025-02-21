
void serialEvent (Serial port)
{
  try {
    data = port.readStringUntil('\n');
    println(data);

    //if (data.startsWith("*")) {
    //  ch = parseInt(data.substring(data.indexOf("*") + 1, data.indexOf(":") ).trim());
    //  rezolution = parseInt(data.substring(data.indexOf(":") + 1, data.indexOf(">") ).trim());
    //  String info[] = data.split(">");
    //  String samples[] = info[1].split(",");

    //  for (int k = 0; k <256; k++) {
    //    vector[k] = parseInt(samples[k].trim());
    //    vector[k] = map(vector[k], 0, 1024, lat/2, 0);
    //  }
    //}
    if (data.startsWith("*:") || data.startsWith("&*:")) {
      if (data.startsWith("&*:")) {
        single_acq = true;
      } else {
        single_acq = false;
      }
      RX = true;

      coding = data.split(":");
      samples = coding[1].split(",");
      sum = 0;

      for (k = 0; k <dim; k++) {
        vector[k] = parseInt(samples[k].trim());
        sum = vector[k] + sum;

        if (vector[k] >= max_volt) {
          max_volt = vector[k];
          min_volt = max_volt;
        }


        if (vector[k] <= min_volt) {
          min_volt = vector[k];
        }

        peak_to_peak = max_volt - min_volt;

        if (k == dim - 1) {
          average = sum/dim;
        }
        vector[k] = map(vector[k], 0, 1024, lat/2 - offset, deflexie - offset);
      }
    } else {
      RX = false;
    }
  }

  catch(Exception e) {
    println("Eroare conversii date");
  }
}


void signal() {

  pas_horiz = (lung+180)/puncte;
  stroke(0, 250, 0);
  strokeWeight(3);

  for (i = 0; i<puncte; i++) {

    if (i<puncte - 1 && index < lung && vector[i] <= lat) {

      //REPREZENTARE SEMNAL CA PUNCTE
      if (dot_butt.state) {
        point(index, vector[i]);
      }
      //REPREZENTARE SEMNAL INTERPOLARE
      if  (line_butt.state) {
        line(index, vector[i], index + pas_horiz, vector[i+1]);
      }
      //REPREZENTARE SEMNAL CA SAMPLE
      if (!line_butt.state && (!dot_butt.state)) {
        line(index, vector[i], index, lat/2 - offset);
      }
    }
    index = index + pas_horiz;
  }


  if (index >=width) {
    if (persist_butt.state) {
      index = 0;
    } else {
      //delay(150);
      delay(20);
      index = 0;
      refresh();
    }
  }
}





//if (ch == 1) {
//  for (i = 0; i < dim; i++) {
//    //point(index, vector[i]);
//    index = index + pas_horiz;
//    if (i>0 && index <= lung) {
//      line(index - pas_horiz, vector[i-1], index, vector[i]);
//    }
//  }

//  if (index > lung) {
//    if (persistance) {
//      index = 0;
//    } else {
//      delay(16);
//      index = 0;
//      refresh();
//    }
//  }
//}




void err_window() {

  fill(0, 0, 200);
  stroke(200, 0, 0);
  rect(width/2-200, height/2-150, 400, 150);
  textSize(30);
  textAlign(CENTER);
  fill(200, 0, 0);
  text("NO CONNECTION!", width/2, height/2-100);
}
