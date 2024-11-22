import functions.ArrayTabulatedFunction;
import functions.FunctionPoint;
import functions.TabulatedFunction;

public class Program7 {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_BLACK = "\u001B[30m";
    public static final String ANSI_RED = "\u001B[31m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_YELLOW = "\u001B[33m";
    public static final String ANSI_BLUE = "\u001b[34;40;1m";
    public static final String ANSI_PURPLE = "\u001B[35m";
    public static final String ANSI_CYAN = "\u001B[36m";
    public static final String ANSI_MAGENTA = "\u001b[35;40;1m";
    public static final String ANSI_WHITE = "\u001B[37m";

    public static void main(String[] args) {
        TabulatedFunction fArr = new ArrayTabulatedFunction(0, 10, new double[] {-1, -2, -3, -4, -5, -6, -7, -8, -9, -10});

        System.out.println(ANSI_MAGENTA + "___________Array___________" + ANSI_RESET);
        for (FunctionPoint point : fArr) {
            System.out.println(point);
        }

        TabulatedFunction fLinked = new ArrayTabulatedFunction(0, 10, new double[] {-10, -20, -30, -40, -50, -60, -70, -80, -90, -100});

        System.out.println(ANSI_MAGENTA + "___________Linked list___________" + ANSI_RESET);
        for (FunctionPoint point : fLinked) {
            System.out.println(point);
        }


    }
}
