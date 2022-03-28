# Embedded device Technical Documentation

## Device description

Describe your device. Don't forget to insert pictures here.

## Code description

Place relevant code snippets here and describe what the code does. No screenshots but code blocks such as:

```c++
void setup(){
    pinMode(13, OUTPUT);    
}

void loop(){
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, HIGH);
    delay(500);
}
```

## Wiring diagram

Use [fritzing](https://fritzing.org/) or a schematic editor to create a readable wiring diagram.

Readable means:
- No diagonal wires
- Minimize wire crossovers
- Wire colors
  - Black for negative voltage
  - Red for positive voltage
  - Every signal a different color, or at least grouped by functionality
- Annotate parts, add text and values

Possible software:
- [KiCAD](https://www.kicad.org/)
- [EasyEDA](https://easyeda.com/)
- [Fritzing](https://fritzing.org/)
- [Eagle](https://www.autodesk.com/products/eagle/overview) as part of Fusion360



## Bill of Materials
