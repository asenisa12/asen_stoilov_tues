
__asm__(".code16\n");
__asm__("jmpl $0x0000, $main\n");


void Word(){
		__asm__ __volatile__ ("movb $'H'  , %al\n");
     __asm__ __volatile__ ("movb $0x0e, %ah\n");
     __asm__ __volatile__ ("int $0x10\n");

     __asm__ __volatile__ ("movb $'E'  , %al\n");
     __asm__ __volatile__ ("movb $0x0e, %ah\n");
     __asm__ __volatile__ ("int $0x10\n");


     __asm__ __volatile__ ("movb $'L'  , %al\n");
     __asm__ __volatile__ ("movb $0x0e, %ah\n");
     __asm__ __volatile__ ("int $0x10\n");



     __asm__ __volatile__ ("movb $'L'  , %al\n");
     __asm__ __volatile__ ("movb $0x0e, %ah\n");
     __asm__ __volatile__ ("int $0x10\n");



     __asm__ __volatile__ ("movb $'O'  , %al\n");
     __asm__ __volatile__ ("movb $0x0e, %ah\n");
     __asm__ __volatile__ ("int $0x10\n");
}

void keypress(){
	 __asm__ __volatile__ (
          "xorw %ax, %ax\n"
          "int $0x16\n"
     );
}

void clrScr(){
	__asm__ __volatile__ (
          "int $0x10" : : "a"(0x03)
     );
     __asm__ __volatile__ (
          "int $0x10" : : "a"(0x0013)
     );
}

void main() {



    Word();

    keypress();

    clrScr();
    int x=100,y=10;
    int color=0;
    for(;;){
 	
    	__asm__ __volatile__ (
          "int $0x10" : : "a"(0x0c00 | color), "c"(x), "d"(y)
     	);

     	if(x<200 && y==10)
     		x++;
     	
     	if(x==200 && y<110)
     		y++;
     	if(x>100 && y==110)
     		x--;

     	if(x==100 && y>10)
     		y--;

     	color++;
     	if(color>10) color =0;
    }

	

}