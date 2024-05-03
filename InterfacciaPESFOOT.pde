import processing.serial.*;
import controlP5.*;
Serial myPort;
ControlP5 cp5;
String nome="Sensore";
PFont font;
int windowPadding=10;
int sliderWidth=60;
int sliderHeight=20;
int [] sensoriParteSinistra = {6,7,11,12,13,14,15};
int totaleLatoSinistro = 0;
int caricoTotale = 0;

void setup()
{
  size(600,600);
  background(64,128,255); 
  font = createFont("Calibri", 20);
  textFont(font);
  
  // I dati raccolti tramite il microcontrollore Arduino vengono trasmessi tramite seriale per essere visualizzati 
  // in un'interfaccia
  cp5 = new ControlP5(this);
  myPort = new Serial(this, "COM3",9600);
  int posX=windowPadding;
  int posY=windowPadding;
  int posTextX = posX+sliderWidth+10;
  for(int i=0;i<16;i++){
    String nomeS=nome + (i+1);
    if(i==8){
     posY=windowPadding;
     posX+=(500-windowPadding*2)-sliderWidth;
     posTextX = posX-100; 
    }
    cp5.addSlider(nomeS).setPosition(posX, posY).setSize(sliderWidth, sliderHeight).setRange(0,255).setColorForeground(color(#FFA000));
    cp5.getController(nomeS).getCaptionLabel().setVisible(false);
    textAlign(LEFT, TOP);
    text(nomeS, posTextX, posY);
    posY+=(500+sliderHeight-windowPadding*2)/8;
  }
  cp5.addSlider("Carico Totale").setPosition(10,530).setSize(sliderWidth, sliderHeight).setRange(0,255).setColorForeground(color(#FFA000));
  cp5.getController("Carico Totale").getCaptionLabel().setVisible(false);
  textAlign(LEFT, TOP);
  text("Carico Totale", 80, 530);
  cp5.addSlider("Carico lato sinistro").setPosition(420,530).setSize(sliderWidth, sliderHeight).setRange(0,255).setColorForeground(color(#FFA000));
  cp5.getController("Carico lato sinistro").getCaptionLabel().setVisible(false);
  textAlign(LEFT, TOP);
  text("Carico lato sinistro", 250,530);
}
void draw()
{
  if(myPort.available() > 0)
  {
    String val = myPort.readStringUntil('\n');
    if (val != null)
    {
      println(val);
      String[]list = split(val,',');
      for(int i=0;i<16;i++)
      {
        String nomeS=nome + (i+1);
        int intValue=0;
        try
        {
          intValue=Integer.parseInt(list[i]);
          caricoTotale += intValue;
        }
        catch(Exception e)
        {
          return;
        }
        // funzione che cerca il valore i all'interno dell'array
        if (isPresent(i))
        {
          totaleLatoSinistro += intValue;
        }
        
        cp5.getController(nomeS).setValue(intValue);
        cp5.getController(nomeS).setColorForeground(colorFromValue(intValue));
        
      }
      
      
      println("Il carico totale sul lato sinistro è: " + totaleLatoSinistro);
      
      float totaleLatoSinistroFloat = map((float)totaleLatoSinistro, 0, 255*7, 0,255);
      float caricoTotaleFloat = map((float)caricoTotale, 0, 255*16,0,255);
      cp5.getController("Carico lato sinistro").setValue((int)totaleLatoSinistroFloat);
      println("Il carico totale sul lato sinistro map è: " + totaleLatoSinistroFloat);
      cp5.getController("Carico lato sinistro").setColorForeground(colorFromValue((int)totaleLatoSinistroFloat));
      cp5.getController("Carico Totale").setValue((int)caricoTotaleFloat);
      cp5.getController("Carico Totale").setColorForeground(colorFromValue((int)caricoTotaleFloat));
      if(totaleLatoSinistro >= 60*caricoTotale/100)
      {
         println("Il carico è sbilanciato sul lato sinistro. Intervenire per bilanciare il carico");
         
      }
      else if(totaleLatoSinistro <= 40*caricoTotale/100 && totaleLatoSinistro > 0)
      {
         println("Il carico è sbilanciato sul lato destro. Intervenire per bilanciare il carico");
      }
      totaleLatoSinistro = 0;
      caricoTotale=0; 
    }
  }
}


int colorFromValue(int value)
{
  if (value <= 128)
  {
    return color(255,(value*2)-1,0);
  }
  else 
  {
    return color(255-(value-128)*2,255,0);
  }
}

boolean isPresent(int index)
{
  boolean probe = false;
  for(int i=0; i<sensoriParteSinistra.length; i++)
  {
    if(sensoriParteSinistra[i] == index)
    {
      probe = true;
    }
  }
  return probe;
}
