class Cursor {

  float x_1;    
  float y_1;    
  float x_2;    
  float y_2;   
  float x_3;    
  float y_3; 
  int move = 0;

  Cursor(float x1, float y1, float x2, float y2, float x3, float y3) {
    x_1 = x1;
    y_1 = y1;
    x_2 = x2;
    y_2 = y2;
    x_3 = x3;
    y_3 = y3;
  }

  void place() {
    stroke(250,250,0);
    fill(250, 250, 50);
    triangle(x_1, y_1+move, x_2, y_2+move, x_3, y_3+move);
  }

  boolean MouseIsOver() {
    if (mouseX > x_2 && mouseX < (x_3 - x_2) && mouseY > y_2 && mouseY < (y_3 - y_2)) {
      return true;
    }
    return false;
  }

}
