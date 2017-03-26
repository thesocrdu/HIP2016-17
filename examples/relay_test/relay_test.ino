int lightpin=3;
int fanpin=2;
int TVpin=4;
int butpin=10;
enum cmdlist
{
  cmd_light1 =1,
  cmd_fan1   =2,
  cmd_TV1    =3,
  cmd_light0 =4,
  cmd_fan0   =5,
  cmd_TV0    =6
};
void setup(){
  pinMode(lightpin,OUTPUT);
  pinMode(fanpin,OUTPUT);
  pinMode(TVpin,OUTPUT);
  pinMode(butpin,INPUT_PULLUP);
 
}
void loop(){
  int butval = digitalRead(butpin);
 if(butval == LOW)
  activate(cmd_light1);
  else if(butval==HIGH)
  deactivate(cmd_light0);
}
void activate (cmdlist mycmd) 
{
  if(mycmd==cmd_light1)
    digitalWrite(lightpin,HIGH);
  else if (mycmd==cmd_fan1)
   digitalWrite(fanpin,HIGH);
  else if (mycmd==cmd_TV1)
    digitalWrite(TVpin,HIGH);
}
 void deactivate (cmdlist mycmd)
{ 
  if(mycmd==cmd_light0)
    
    digitalWrite(lightpin,LOW);
  else if (mycmd==cmd_fan0)
    digitalWrite(fanpin,LOW);
  else if (mycmd==cmd_TV0)
    digitalWrite(TVpin,LOW);  
}


