
import java.util.function.Function;

class Main{
    public static void main(String[] args){
        System.out.println(new test().A(5));
    }
}

class test{
    public int A(int x){
        Function<Integer,Integer> inc;
        x = a + b + c;
        inc = ((y) -> y + 1);
        return inc.apply(x);
    }
}