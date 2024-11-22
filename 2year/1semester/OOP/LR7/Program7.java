import functions.ArrayTabulatedFunction;
import functions.Function;
import functions.FunctionPoint;
import functions.LinkedListTabulatedFunction;
import functions.TabulatedFunction;
import functions.TabulatedFunctions;
import functions.basic.Cos;
import functions.basic.Sin;

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

        System.out.println(ANSI_MAGENTA + "___________Iterators___________" + ANSI_RESET);

        System.out.println(ANSI_GREEN + "-- Array:" + ANSI_RESET);
        for (FunctionPoint point : fArr) {
            System.out.println(point);
        }

        TabulatedFunction fLinked = new ArrayTabulatedFunction(0, 10, new double[] {-10, -20, -30, -40, -50, -60, -70, -80, -90, -100});

        System.out.println(ANSI_GREEN + "-- Linked:" + ANSI_RESET);
        for (FunctionPoint point : fLinked) {
            System.out.println(point);
        }

        System.out.println(ANSI_MAGENTA + "___________Factories___________" + ANSI_RESET);
        Function sin = new Sin();

        System.out.println(ANSI_GREEN + "-- Initial factory:" + ANSI_RESET);
        TabulatedFunction sinTab = TabulatedFunctions.tabulate(sin, 0, Math.PI, 11);
        
        System.out.println(sinTab.getClass());
        
        System.out.println(ANSI_GREEN + "-- Set array factory:" + ANSI_RESET);
        TabulatedFunctions.setTabulatedFunctionFactory(new ArrayTabulatedFunction.ArrayTabulatedFunctionFactory());

        sinTab = TabulatedFunctions.tabulate(sin, 0, Math.PI, 11);
        System.out.println(sinTab.getClass());

        System.out.println(ANSI_GREEN + "-- Set linked factory:" + ANSI_RESET);
        TabulatedFunctions.setTabulatedFunctionFactory(new LinkedListTabulatedFunction.LinkedListTabulatedFunctionFactory());

        sinTab = TabulatedFunctions.tabulate(sin, 0, Math.PI, 11);
        System.out.println(sinTab.getClass());


        System.out.println(ANSI_MAGENTA + "___________Reflection___________" + ANSI_RESET);

        System.out.println(ANSI_GREEN + "-- createTabulatedFunction(leftX, rightX, pointsCount, Class) | Array class:" + ANSI_RESET);
        TabulatedFunction tabFunc = TabulatedFunctions.createTabulatedFunction(0, 10, 3, ArrayTabulatedFunction.class);
        System.out.println(tabFunc.getClass());
        System.out.println(tabFunc);

        System.out.println(ANSI_GREEN + "-- createTabulatedFunction(leftX, rightX, values, Class) | Array class:" + ANSI_RESET);
        tabFunc = TabulatedFunctions.createTabulatedFunction(0, 10, new double[] { 0, 10 }, ArrayTabulatedFunction.class);
        System.out.println(tabFunc.getClass());
        System.out.println(tabFunc);

        System.out.println(ANSI_GREEN + "-- createTabulatedFunction(points, Class) | LinkedList class:" + ANSI_RESET);
        tabFunc = TabulatedFunctions.createTabulatedFunction(new FunctionPoint[] { new FunctionPoint(0,0), new FunctionPoint(10,10) }, LinkedListTabulatedFunction.class);
        System.out.println(tabFunc.getClass());
        System.out.println(tabFunc);

        System.out.println(ANSI_GREEN + "-- tabulate(..., Class) | LinkedList class:" + ANSI_RESET);
        tabFunc = TabulatedFunctions.tabulate(new Cos(), 0, Math.PI, 11, LinkedListTabulatedFunction.class);
        System.out.println(tabFunc.getClass());
        System.out.println(tabFunc);
    }
}
