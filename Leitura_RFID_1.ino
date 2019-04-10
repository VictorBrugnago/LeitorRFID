#define FDL_CHAR 3
const int T_BUFFER = 20;
char buffer[T_BUFFER + 1];

const char id[]="7F0045BA66E6"; // ID TAG


void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    int tamanho = Mensagem(FDL_CHAR);
    String texto = buffer;
    Serial.print("CARTAO Decodificado!. ID: " + texto);
    //Serial.print(texto);
    if (texto.compareTo(id) == 0){
      Serial.println("");
      Serial.println("TAG Encontrada!");
      Serial.println("");
    } else {
      Serial.println("");
      Serial.println("TAG Nao Encontrada...");
      Serial.println("");
    }
  }
}

/*void loop() {
  if (Serial.available()){
    int tamanho = Mensagem(FDL_CHAR);
    char* texto = buffer;
    if(texto.compareTo(id)){
      Serial.println("TAG Encontrada");
    } else {
      Serial.print("TAG nao encontrada. ID: ");
      Serial.println(buffer);
    }
  }
}*/

int Mensagem(char eol){
  int soma=0;
  char c = eol - 1;
  while(c != eol){
    if(Serial.available()){
      c = Serial.read();
      if((c != 2) && (c != 13) && (c != 10)){ // Detecta STX, CR, LF
        buffer[soma++] = c;
      }
    }
    if(soma >= T_BUFFER){
      while(Serial.available()){
        Serial.read(); // Flush
      }
      break;
    }
  }
  buffer[T_BUFFER] = 0;
  if (soma < T_BUFFER){
    buffer[soma - 1] = 0;
  }
  return(soma - 1);
}
