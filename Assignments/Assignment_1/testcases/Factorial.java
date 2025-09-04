#define NUM() (10+0)
#define ONE() (1+0)
#define SQUARE(x) ((x)*(x))
#define PRINTSOMETHING(x) {System.out.println(x);}
class Factorial{
    public static void main(String[] a){
        System.out.println(new Fac().ComputeFac(NUM()));
    }
}

class Fac {
    public int ComputeFac(int num, int a){
        int num_aux ;
        int temp ;
        temp = SQUARE(3) ;
        if ((num <= 1)&&(num != 1))
            num_aux = ONE() ;
        else
            num_aux = num * (this.ComputeFac(num-1)) ;
        return num_aux ;
    }
}
