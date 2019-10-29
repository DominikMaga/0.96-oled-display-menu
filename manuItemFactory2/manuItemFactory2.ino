#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ClickEncoder.h>
#include <TimerOne.h>
#include <stdio.h>
#include <stdlib.h>

ClickEncoder *encoder;
int16_t last, value;

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

boolean up = false;
boolean down = false;
boolean middle = false;

void setup() {


  //  FactoryMenuItems *pFactoryItems = new FactoryMenuItems("intItem");
  // TypeMenuItem * pMenuItem = pFactoryItems -> getMenuItem();
  //    pVehicle->printVehicle();
  Serial.begin(9600);

  //random kradziony
  pinMode(13, OUTPUT); // signal ready to go and then wait a bit
  digitalWrite(13, HIGH);
  delay(2000);
  //
  encoder = new ClickEncoder( A1, A0, A2);
  encoder->setAccelerationEnabled(false);
  //
  display.begin();
  display.clearDisplay();
  //
  Timer1.initialize(1000);
  // Timer1.attachInterrupt(timerIsr);
  //
  last = encoder->getValue();

}

void loop() {
  if (middle) //Middle Button is Pressed               /wcisniecie przycisku enkodera
  {
    middle = false;
  }
}

int resetValuesMore(int i, int MinValue, int MaxValue) { //przekręcenie licznika w górę
  i += 1;
  if (i > MaxValue ) {  ///sizeof(menuItem)
    i = MinValue;
  }
  return i;
}

int resetValuesLess(int i, int MinValue, int MaxValue) {  // przekręcenie licznika w dół
  i -= 1;
  if (i < MinValue) { //sizeof(menuItem)
    i = MaxValue;
  }
  return i;
}

class TypeMenuItem {
  protected:
    String name;
  public:

    virtual String getName() = 0;
    virtual void setName(String s) = 0;
    virtual int getType() = 0;

};
class IntItem : public TypeMenuItem {
  private:
    int value = 0;
    int defaultValue;
  public:

    void setValue(int v) {
      value = v;
    }
    void setDefaultValue(int v) {
      defaultValue = v;
    }
    void reset() {
      value = defaultValue;
    }
    int getValue() {
      return value;
    }
    void setName(String s) {
      name = s;
    }
    String getName()  {
      return name;
    }
    void displayValue() {
      display.setTextSize(1);
      display.clearDisplay();
      display.setTextColor(WHITE, BLACK);
      display.setCursor(32, 0);
      display.print(getName());
      display.drawFastHLine(0, 10, 83, BLACK);
      display.setCursor(5, 8);
      display.print("Value");
      display.setTextSize(2);
      display.setCursor(40, 8);
      display.print(getValue());
      display.setTextSize(2);
      display.display();
    }
    int getType() {
      return 0;
    }
};
class FloatItem : public TypeMenuItem {
  private:
    float value = 0;
    float defaultValue;
  public:

    void setValue(float v) {
      value = v;
    }
    void setDefaultValue(float v) {
      defaultValue = v;
    }
    void reset() {
      value = defaultValue;
    }
    float getValue() {
      return value;
    }

    void setName(String s) {
      name = s;
    }
    String getName()  {
      return name;
    }
    void displayValue() {
      display.setTextSize(1);
      display.clearDisplay();
      display.setTextColor(WHITE, BLACK);
      display.setCursor(32, 0);
      display.print(getName());
      display.drawFastHLine(0, 10, 83, BLACK);
      display.setCursor(5, 8);
      display.print("Value");
      display.setTextSize(2);
      display.setCursor(40, 8);
      display.print(getValue());
      display.setTextSize(2);
      display.display();
    }
    int getType() {
      return 0;
    }
};
class StrItem : public TypeMenuItem {
  private:
    String tableValues[];
    int currentValue = 0;
  public:
    void setTableValues(String tab[]) {
      tableValues[sizeof(tab)];
      for ( int i = 0; i < sizeof(tab); i++ ) {
        tableValues[i] = tab[i];
      }
    }
    void reset() {
      currentValue = 0;
    }
    void next() {
      resetValuesMore(currentValue, 0, (sizeof(tableValues) - 1));
    }
    void previous() {
      resetValuesLess(currentValue, 0, (sizeof(tableValues) - 1));
    }
    String getValue() {
      return tableValues[currentValue];
    }


    void setName(String s) {
      name = s;
    }
    String getName()  {
      return name;
    }
    void displayValue() {
      display.setTextSize(1);
      display.clearDisplay();
      display.setTextColor(WHITE, BLACK);
      display.setCursor(32, 0);
      display.print(getName());
      display.drawFastHLine(0, 10, 83, BLACK);
      display.setCursor(5, 8);
      display.print("Value");
      display.setTextSize(2);
      display.setCursor(40, 8);
      display.print(getValue());
      display.setTextSize(2);
      display.display();
    }
    int getType() {
      return 0;
    }
};

class BoolItem : public TypeMenuItem {
  private:
    bool value;
  public:
    void setValue(bool v) {
      value = v;
    }
    bool getValue() {
      return value;
    }
    void changeValue() {
      value = !value;
    }
    void setName(String s) {
      name = s;
    }
    String getName()  {
      return name + ": " + (value ? "on" : "off") ;
    }
    int getType() {
      return 1;
    }

};
class MethodItem : public TypeMenuItem {
  private:
    bool value;
  public:
    void setValue(bool v) {
      value = v;
    }
    bool getValue() {
      return value;
    }
    void changeValue() {
      value = !value;
    }
    void setName(String s) {
      name = s;
    }
    String getName()  {
      return name;
    }
    int getType() {
      return 2;
    }
//getinstance
};

class FactoryMenuItems {
  public:
    FactoryMenuItems(String typeItem)  {

      // Client explicitly creates classes according to type
      if (typeItem == "intItem")
        pMenuItem = new IntItem();
      else if (typeItem == "floatItem")
        pMenuItem = new FloatItem();
      else if (typeItem == "strItem")
        pMenuItem = new StrItem();
      else if (typeItem == "methodItem")
        pMenuItem = new MethodItem();
      else if (typeItem == "boolItem")
        pMenuItem = new BoolItem();
      else
        pMenuItem = NULL;
    }

    ~FactoryMenuItems()   {
      if (pMenuItem)
      {
        delete[] pMenuItem;
        pMenuItem = NULL;
      }
    }
    TypeMenuItem* getTypeMenuItem() {
      return pMenuItem;
    }

  private:
    TypeMenuItem *pMenuItem;
};
class Menu {
    int page = 1;
    const int fontPos1 = 8;         //kolejne pozycje pixeli na wyświetlaczu
    const int fontPos2 = 16;        //do konstruktora
    const int fontPos3 = 24;
    bool menuHighlight[3] = { 1, 0, 0 };
    TypeMenuItem * itemsArray[];
    int l = 0, m = 1, n = 2; //zmienne potrzebne do ustalenia wyświetlania przedmiotów w menu
  public:
    void setSize(int size) {
      itemsArray[size];
    }
    void setItems() {
      FactoryMenuItems *integerFactoryItems = new FactoryMenuItems("intItem");

      TypeMenuItem * manaCostItem = integerFactoryItems -> getTypeMenuItem();
      itemsArray[0] = manaCostItem;
      itemsArray[0]->setName("ManaCost");
      //  TypeMenuItem itemsArray;
      //  itemsArray=new IntItem;
      //  itemsArray[1]->setName("ManaCost");
    }
    void addItem(TypeMenuItem * MI) {
      itemsArray[sizeof(itemsArray)] = MI;
    }

    //    void setMenuItem(String a) {        // zmienia nazwe przedmiotu w menu np. dla boola
    //
    //      if (menuHighlight[0]) {
    //        itemsArray[l] = a;
    //      }
    //      if (menuHighlight[1]) {
    //        itemsArray[m] = a;
    //      }
    //      if (menuHighlight[2]) {
    //        itemsArray[n] = a;
    //      }
    //
    //    }
    int getMenuItem() {           // zwraca aktualnie wybrany przedmiot w Menu
      if (menuHighlight[0]) {
        return l;
      }
      if (menuHighlight[1]) {
        return m;
      }
      if (menuHighlight[2]) {
        return n;
      }
    }

    void button() {
      if (page == 1) {

        //
        //            if(dynamic_cast<BoolItem*>(itemsArray[getMenuItem()]) != nullptr){
        switch (itemsArray[getMenuItem]->getType()) {
          case 0:
            page = 2;
            break;
          case 1:
            itemsArray[getMenuItem]->changeValue();
            break;
          case 2

        }
        //    }
      };
