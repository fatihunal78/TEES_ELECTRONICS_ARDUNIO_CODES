class Button {

  String label;
  float x;    // top left corner x position
  float y;    // top left corner y position
  float w;    // width of button
  float h;    // height of button
  int cl;  // color
  int r; 
  int g;
  int b;
  int canal = 1;

  boolean state = false;
  boolean prevState = false;
  int opac = 180;

  Button(String labelB, float xpos, float ypos, float widthB, float heightB, int red, int green, int blue) {
    label = labelB;
    x = xpos;
    y = ypos;
    w = widthB;
    h = heightB;
    r = red;
    g = green;
    b = blue;
  }

  void place() {
    noStroke();
    if (canal == 1) {
      fill(200, 200, 0); //ultimul argument = opacitatea
    }
    if(canal == 2){
      fill(250, 0, 50);
    }
    rect(x, y, w, h, 10);
    noFill();
    if (state) {
      stroke(0, 250, 0);
    }
    if (!state) {
      stroke(250, 250, 250);
    }
    strokeWeight(3.1);
    rect(x, y, w, h, 7);
    fill(0);
    textSize(15);
    textAlign(CENTER);
    text(label, x+w/2, y+h/1.5);
  }

  boolean MouseIsOver() {
    if (mouseX > x && mouseX < (x + w) && mouseY > y && mouseY < (y + h)) {
      return true;
    }
    return false;
  }
  void select(int rr, int gg, int bb) {
    r = rr;
    b = bb;
    g = gg;
  }

  void opacity(int opc) {
    opac = opc;
  }
}
