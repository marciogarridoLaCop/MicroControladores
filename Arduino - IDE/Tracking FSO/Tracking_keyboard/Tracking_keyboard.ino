
/* PROJETO DE LEITURA ANÁLISE DE TURBULENCIAS ATMOSFÉRICAS
 * UNIVERSIDADE FEDERAL FLUMINENSE
 * ALUNOS:MARCIO GARRIDO/WEBER GAIA/JANAINA NASCIMENTO
 * 2019.2
 * PROFESSOR DR. VINICIUS NUNES / DR. PABLO 
 * 
 * CONTROLE DO SERVO MECANISMO PARA POSICIONAMENTO DO LASER
 * MODULO DE TRANSMISSÃO
 */

//------------------------------------------VARIAVEIS E LIBS---------------------------------------------  

#include <AFMotor.h> //biblioteca do shield motor LadyAda  
AF_Stepper motorY(250, 1); //motor com 500 passos/revolução no port M1 e M2
AF_Stepper motorX(250, 2); //motor com 500 passos/revolução no port M3 e M4
int passos,leitura= 0;
String conteudo = "";
//------------------------------------------VARIAVEIS E LIBS---------------------------------------------  

//------------------------------------------CONFIGURACAO INICIAL-----------------------------------------  

void setup() {
  Serial.begin(9600); //comunicação serial
  motorY.setSpeed(1); //10 rpm, velocidade de rotação
  motorX.setSpeed(1); //10 rpm, velocidade de rotação
  Serial.println ("Digite o número de Passos:");
 }
//------------------------------------------CONFIGURACAO INICIAL-----------------------------------------  


//------------------------------------------VALIDAR OPCAO------------------------------------------------

void loop() 
{
    if (Serial.available())
    {
    valiando_entrada();
    }
}

//------------------------------------------VALIDAR OPCAO------------------------------------------------


//--------------------------------------------LER SERIAL-------------------------------------------------  

String leStringSerial(){
  Serial.flush();
  char caractere;
  conteudo="";
  // Enquanto receber algo pela serial
  while(Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n'){
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }  
  return conteudo;
}
//--------------------------------------------LER SERIAL-------------------------------------------------


//------------------------------------------VALIDAR OPCAO------------------------------------------------
void valiando_entrada(){
if (Serial.available() > 0){
    // Lê toda string recebida
    String recebido = leStringSerial();
   
    if (recebido == "u")
    {            
              motorY.step(passos, FORWARD, SINGLE);
              Serial.print("UP +Y");
              Serial.print(passos); 
              Serial.println(" Passos");
                 
    }
    if (recebido == "d")
    {
              motorY.step(passos, BACKWARD, SINGLE);
              Serial.print("DOWN -Y");
              Serial.print(passos);
              Serial.println(" Passos");
              
    }
    if (recebido == "r")
    {
              motorX.step(passos, FORWARD, SINGLE);
              Serial.print("RIGHT +X");
              Serial.print(passos );
              Serial.println(" Passos");
              
    }
    if (recebido == "l")
    {
              motorX.step(passos, BACKWARD, SINGLE);
              Serial.print("LEFT -X");
              Serial.print(passos);
              Serial.println(" Passos");
    }
    
else
      if (leitura ==0)
      {
        Serial.print("Número de passos: ");
        Serial.println(conteudo);
        passos=conteudo.toInt();
        leitura=leitura+1;
      } 
      
  }
  Serial.println(" Digite agora a direção : u para UP, d para DOWN, R para RIGHT ou L para LEFT");         
}
