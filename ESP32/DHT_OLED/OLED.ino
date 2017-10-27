void SetupOLED() {
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);  
}

void drawText1(String textLine1) {
  display.clear();
  display.drawString(0, 0, textLine1);
  display.display();
}

void drawText3(String textLine1, String textLine2, String textLine3) {
  display.clear();
  display.drawString(0, 0, textLine1);
  display.drawString(0, 20, textLine2);
  display.drawString(0, 45, textLine3);
  display.display();
}

