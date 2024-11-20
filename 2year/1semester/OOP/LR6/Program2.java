import functions.Function;
import functions.FunctionPoint;
import functions.FunctionPointIndexOutOfBoundsException;
import functions.Functions;
import functions.InappropriateFunctionPointException;
import functions.LinkedListTabulatedFunction;
import functions.TabulatedFunction;
import functions.TabulatedFunctions;
import functions.basic.Cos;
import functions.basic.Exp;
import functions.basic.Log;
import functions.basic.Sin;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.text.DecimalFormat;

public class Program2 {
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
        TabulatedFunction tabFuncLin = new LinkedListTabulatedFunction(-2, 2, new double[]{ -8, -3, 2, 7, 12 });
        
        
        System.out.println("___________y=5x+2___________");
        System.out.println("x     |  y");
        System.out.println("-2:   |" + tabFuncLin.getFunctionValue(-2));
        System.out.println("-1.5: |" + tabFuncLin.getFunctionValue(-1.5));
        System.out.println("-1:   |" + tabFuncLin.getFunctionValue(-1));
        System.out.println("-0.5: |" + tabFuncLin.getFunctionValue(-0.5));
        System.out.println("0:    |"  + tabFuncLin.getFunctionValue(0));
        System.out.println("0.1:  |" + tabFuncLin.getFunctionValue(0.1));
        System.out.println("0.5:  |" + tabFuncLin.getFunctionValue(0.5));
        System.out.println("1:    |"  + tabFuncLin.getFunctionValue(1));
        System.out.println("1.5:  |" + tabFuncLin.getFunctionValue(1.5));
        System.out.println("2:    |"  + tabFuncLin.getFunctionValue(2));
        System.out.println("2:    |"  + tabFuncLin.getFunctionValue(5));

        
        System.out.println("___________y=5x+2(actual values)___________");
        for (int i = 0; i < tabFuncLin.getPointsCount(); i++) {
            System.out.println(tabFuncLin.getPointX(i) + ":   |" + tabFuncLin.getPointY(i));
            
        }

        TabulatedFunction tabFunc = new LinkedListTabulatedFunction(-3, 3, new double[]{ -54, -2, 2, 54 });
        System.out.println("___________y=2x^3___________");
        System.out.println("x     |  y");
        System.out.println("-3:   |" + tabFunc.getFunctionValue(-3));
        System.out.println("-2:   |"  + tabFunc.getFunctionValue(-2));
        System.out.println("-1:   |"  + tabFunc.getFunctionValue(-1));
        System.out.println("0:   |"  + tabFunc.getFunctionValue(0));
        System.out.println("1:    |" + tabFunc.getFunctionValue(1));
        System.out.println("2:    |"  + tabFunc.getFunctionValue(2));
        System.out.println("3:    |" + tabFunc.getFunctionValue(3));
        

        System.out.println("___________y=2x^3(actual values)___________");
        System.out.println("x     |  y");
        for (int i = 0; i < tabFunc.getPointsCount(); i++) {
            System.out.println(tabFunc.getPointX(i) + ":   |" + tabFunc.getPointY(i));
            
        }

        tabFunc.deletePoint(0);
        tabFunc.deletePoint(0);
        try {
            tabFunc.addPoint(new FunctionPoint(0, 0));

            tabFunc.deletePoint(2);
            tabFunc.addPoint(new FunctionPoint(2, 16));
        } catch (InappropriateFunctionPointException e) {
            System.out.println("huh..... error");
            
        }

        System.out.println("___________y=2x^3(actual values) (updated)___________");
        System.out.println("x     |  y");
        for (int i = 0; i < tabFunc.getPointsCount(); i++) {
            System.out.println(tabFunc.getPointX(i) + ":   |" + tabFunc.getPointY(i));
        }

        System.out.println("___________y=2x^3 (updated)___________");
        System.out.println("x     |  y");
        System.out.println("-3:   |" + tabFunc.getFunctionValue(-3));
        System.out.println("-2:   |"  + tabFunc.getFunctionValue(-2));
        System.out.println("-1:   |"  + tabFunc.getFunctionValue(-1));
        System.out.println("0:   |"  + tabFunc.getFunctionValue(0));
        System.out.println("1:    |" + tabFunc.getFunctionValue(1));
        System.out.println("2:    |"  + tabFunc.getFunctionValue(2));
        System.out.println("3:    |" + tabFunc.getFunctionValue(3));


        System.out.println("Let's test resizing....... and add some stuff");
        try {
            tabFunc.addPoint(new FunctionPoint(.1, 0.002));
            tabFunc.addPoint(new FunctionPoint(.2, 0.016));
            tabFunc.addPoint(new FunctionPoint(.3, 0.054));
            tabFunc.addPoint(new FunctionPoint(.4, 0.128));
            tabFunc.addPoint(new FunctionPoint(.5, 0.25));
            tabFunc.addPoint(new FunctionPoint(.6, 0.432));
            tabFunc.addPoint(new FunctionPoint(.7, 0.686));
            tabFunc.addPoint(new FunctionPoint(.8, 1.024));
            tabFunc.addPoint(new FunctionPoint(.9, 1.458));
        } catch (Exception e) {
            System.out.println("huh..... error");
        }

        System.out.println("___________y=2x^3(actual values) (+ 9 points 0.1-0.9)___________");
        System.out.println("x     |  y");
        for (int i = 0; i < tabFunc.getPointsCount(); i++) {
            System.out.println(tabFunc.getPointX(i) + ":   |" + tabFunc.getPointY(i));
        }

        System.out.println("___________constructor exceptions___________");
        try {
            TabulatedFunction _ = new LinkedListTabulatedFunction(3, -3, new double[]{ -54, -2, 2, 54 });
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }


        try {
            TabulatedFunction _ = new LinkedListTabulatedFunction(-3, 3, new double[]{ -54});
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }
        
        try {
            TabulatedFunction func = new LinkedListTabulatedFunction(-3, 3, new double[]{ -54, -2, 2, 54 });
            func.getPoint(4);

        } catch (FunctionPointIndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }
        
        try {
            TabulatedFunction func = new LinkedListTabulatedFunction(-3, 3, new double[]{ -54, -2, 2, 54 });
            func.setPoint(5, new FunctionPoint());

        } catch (FunctionPointIndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        } catch (InappropriateFunctionPointException e) {}

        try {
            TabulatedFunction func = new LinkedListTabulatedFunction(-3, 3, new double[]{ -54, -2, 2, 54 });
            func.getPointX(6);

        } catch (FunctionPointIndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }

        try {
            TabulatedFunction func = new LinkedListTabulatedFunction(-3, 3, new double[]{ -54, -2, 2, 54 });
            func.setPointX(7, 9);

        } catch (FunctionPointIndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        } catch (InappropriateFunctionPointException e) {}

        try {
            TabulatedFunction func = new LinkedListTabulatedFunction(-3, 3, new double[]{ -54, -2, 2, 54 });
            func.getPointY(8);

        } catch (FunctionPointIndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }

        try {
            TabulatedFunction func = new LinkedListTabulatedFunction(-3, 3, new double[]{ -54, -2, 2, 54 });
            func.setPointY(9, 1);

        } catch (FunctionPointIndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }

        try {
            TabulatedFunction func = new LinkedListTabulatedFunction(-3, 3, new double[]{ -54, -2, 2, 54 });
            func.deletePoint(10);

        } catch (FunctionPointIndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }

        try {
            TabulatedFunction func = new LinkedListTabulatedFunction(-3, 3, new double[]{ -54, -2, 2, 54 });
            func.setPoint(2, new FunctionPoint(4,10));

        } catch (InappropriateFunctionPointException e) {
            System.out.println(e.getMessage());
        }

        try {
            TabulatedFunction func = new LinkedListTabulatedFunction(-3, 3, new double[]{ -54, -2, 2, 54 });
            func.setPointX(1, 138);

        } catch (InappropriateFunctionPointException e) {
            System.out.println(e.getMessage());
        }

        try {
            TabulatedFunction func = new LinkedListTabulatedFunction(-3, 3, new double[]{ -54, -2, 2, 54 });
            func.addPoint(new FunctionPoint(-3, 54));

        } catch (InappropriateFunctionPointException e) {
            System.out.println(e.getMessage());
        }

        try {
            TabulatedFunction func = new LinkedListTabulatedFunction(-3, 3, new double[]{ -54, -2, 2, 54 });
            func.deletePoint(0);
            func.deletePoint(0);
            func.deletePoint(0);
            func.deletePoint(0);
            func.deletePoint(0);

        } catch (IllegalStateException e) {
            System.out.println(e.getMessage());
        }

        //X out of order
        try {
            FunctionPoint[] points = new FunctionPoint[]
            {
                new FunctionPoint(-1, -101),
                new FunctionPoint(0, 100),
                new FunctionPoint(1, 101),
                new FunctionPoint(2, 102),
                new FunctionPoint(-5, 103),
                new FunctionPoint(4, 104),
                new FunctionPoint(5, 105)
            };

            TabulatedFunction func = new LinkedListTabulatedFunction(points);

        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }

        System.out.println("___________optimizations___________");
        
        TabulatedFunction func = new LinkedListTabulatedFunction(-3, 3, new double[]{ -1,-2,-3,-4,-5,-6,-7,-8,-9,-10 });
        //initialize last accessed node
        System.out.println("At index 5:" + func.getPoint(5).getY());
        //should be optimized
        System.out.println("At index 8:" + func.getPoint(8).getY());
        //should be optimized
        System.out.println("At index 6:" + func.getPoint(6).getY());

        //ЛАБОРАТОРНАЯ РАБОТА 4
        //ТРИГОНОМЕТРИЧЕСКИЕ ФУНКЦИИ
        System.out.println(ANSI_BLUE+"____trig functions___________________________________________________________________________________________"+ANSI_RESET);
        DecimalFormat format = new DecimalFormat("#.###");
        System.out.println(ANSI_MAGENTA + "___________sin___________" + ANSI_RESET);
        Function sin = new Sin();
        outputFuncWithStep(sin, 0, 2*Math.PI, 0.1, format);

        System.out.println(ANSI_MAGENTA + "___________cos___________" + ANSI_RESET);
        Function cos = new Cos();
        outputFuncWithStep(cos, 0, 2*Math.PI, 0.1, format);

        System.out.println(ANSI_BLUE+"____trig functions (tabulated)___________________________________________________________________________________________" +  ANSI_RESET);

        System.out.println(ANSI_MAGENTA + "___________sin (tabulated)___________" + ANSI_RESET);
        TabulatedFunction sinTab = TabulatedFunctions.tabulate(sin, 0, 2*Math.PI, 10);
        outputFuncWithStep(sinTab, 0, 2*Math.PI, 0.1, format);

        System.out.println(ANSI_MAGENTA + "___________cos (tabulated)___________"+ ANSI_RESET);
        TabulatedFunction cosTab = TabulatedFunctions.tabulate(cos, 0, 2*Math.PI, 10);
        outputFuncWithStep(cosTab, 0, 2*Math.PI, 0.1, format);

        System.out.println(ANSI_MAGENTA + "_________Сумма квадратов табулированных косинуса и синуса___________" + ANSI_RESET);
        Function squaredSum = Functions.sum(Functions.power(sinTab, 2), Functions.power(cosTab, 2));
        outputFuncWithStep(squaredSum, 0, 2*Math.PI, 0.1, format);

        System.out.println(ANSI_BLUE+"____streams___________________________________________________________________________________________" + ANSI_RESET);
        System.out.println(ANSI_MAGENTA + "_________Сумма квадратов табулированных косинуса и синуса [updated: cos(0) = 5] ___________" + ANSI_RESET);
        try {
            cosTab.setPoint(0, new FunctionPoint(0, -5));
            
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        outputFuncWithStep(squaredSum, 0, 2*Math.PI, 0.1, format);

        System.out.println(ANSI_MAGENTA + "_________tabulated EXP [initial] ___________" + ANSI_RESET);
        TabulatedFunction expTab = TabulatedFunctions.tabulate(new Exp(), 0, 10, 11);
        outputFuncWithStep(expTab, 0, 10, 1, format);

        try {
            FileWriter writer = new FileWriter("serialized_functions/tabulated_exponent");
            TabulatedFunctions.writeTabulatedFunction(expTab, writer);
            writer.close();
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }

        System.out.println(ANSI_MAGENTA + "_________tabulated EXP [from file] ___________" + ANSI_RESET);
        try {
            FileReader reader = new FileReader("serialized_functions/tabulated_exponent");
            TabulatedFunction expTabFile = TabulatedFunctions.readTabulatedFunction(reader);
            reader.close();
            outputFuncWithStep(expTabFile, 0, 10, 1, format);
            
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        System.out.println(ANSI_MAGENTA + "_________tabulated LOG [initial] ___________" + ANSI_RESET);

        TabulatedFunction logTab = TabulatedFunctions.tabulate(new Log(Math.E), 1, 10, 10);
        outputFuncWithStep(logTab, 1, 10, 1, format);
        try {
            FileOutputStream filestream = new FileOutputStream("serialized_functions/tabulated_exponent_streamed");
            TabulatedFunctions.outputTabulatedFunction(logTab, filestream);
            filestream.close();
            
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        System.out.println(ANSI_MAGENTA + "_________tabulated LOG [from file] ___________" + ANSI_RESET);
        try {
            FileInputStream reader = new FileInputStream("serialized_functions/tabulated_exponent_streamed");
            TabulatedFunction logTabFile = TabulatedFunctions.inputTabulatedFunction(reader);
            reader.close();
            outputFuncWithStep(logTabFile, 1, 10, 1, format);
            
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        System.out.println(ANSI_BLUE + "____serialization___________________________________________________________________________________________" + ANSI_RESET);
        System.out.println(ANSI_MAGENTA + "_________tabulated ln(exp(x)) [initial serialized] ___________" + ANSI_RESET);

        TabulatedFunction logExpTab = TabulatedFunctions.tabulate(Functions.composition(new Log(Math.E), new Exp()), 0, 10, 11);
        outputFuncWithStep(logExpTab, 0, 10, 1, format);
        try {
            FileOutputStream filestream = new FileOutputStream("serialized_functions/tabulated_exponent_serializable");
            ObjectOutputStream outputstream = new ObjectOutputStream(filestream);
            outputstream.writeObject(logExpTab);
            filestream.close();

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        System.out.println(ANSI_MAGENTA + "_________tabulated ln(exp(x)) [from file serialized] ___________" + ANSI_RESET);
        try {
            FileInputStream reader = new FileInputStream("serialized_functions/tabulated_exponent_serializable");
            ObjectInputStream inputstream = new ObjectInputStream(reader);
            TabulatedFunction logExpTabFile = (TabulatedFunction)inputstream.readObject();
            inputstream.close();
            outputFuncWithStep(logExpTabFile, 1, 10, 1, format);

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        //LR5

        System.out.println(ANSI_BLUE+"____LR5___________________________________________________________________________________________"+ANSI_RESET);

        System.out.println(ANSI_MAGENTA + "___________sin___________" + ANSI_RESET);
        TabulatedFunction sin2 = TabulatedFunctions.tabulate(new Sin(), -1, 1, 10);
        System.out.println(ANSI_GREEN + "hashcode: " + ANSI_RESET + sin2.hashCode());
        System.out.println(sin2.toString());
        try {
            sin2.addPoint(new FunctionPoint(0.5, 0.5));
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        System.out.println("");
        System.out.println(ANSI_GREEN + "-- Added (0.5, 0.5)" + ANSI_RESET);
        System.out.println(ANSI_GREEN + "hashcode: " + ANSI_RESET + sin2.hashCode());
        System.out.println(sin2.toString());

        System.out.println(ANSI_MAGENTA + "___________cos___________" + ANSI_RESET);
        TabulatedFunction cos2 = TabulatedFunctions.tabulate(new Cos(), -1, 1, 10);
        System.out.println(ANSI_MAGENTA+ "hashcode: " + ANSI_RESET + cos2.hashCode());
        System.out.println(cos2.toString());

        cos2.deletePoint(3);
        System.out.println("");
        System.out.println(ANSI_GREEN + "-- Removed at 3" + ANSI_RESET);
        System.out.println(ANSI_GREEN + "hashcode: " + ANSI_RESET + cos2.hashCode());
        System.out.println(cos2.toString());

        System.out.println(ANSI_MAGENTA + "___________cloned cos:___________" + ANSI_RESET);
        TabulatedFunction clonedCos2 = (TabulatedFunction)cos2.clone();
        System.out.println(ANSI_GREEN + "hashcode: " + ANSI_RESET + clonedCos2.hashCode());
        System.out.println(clonedCos2.toString());

        clonedCos2.setPointY(0, -0.666);
        System.out.println("");
        System.out.println(ANSI_GREEN + "-- Changed Y at 0 to -0.666" + ANSI_RESET);
        System.out.println(ANSI_GREEN + "hashcode: " + ANSI_RESET + clonedCos2.hashCode());
        System.out.println(clonedCos2.toString());
        System.out.println(ANSI_GREEN + "-- Original cos:" + ANSI_RESET);
        System.out.println(cos2.toString());


        System.out.println(ANSI_MAGENTA + "___________array vs linked, same contents:___________" + ANSI_RESET);
        TabulatedFunction funcLink = new LinkedListTabulatedFunction(-2, 2, new double[]{ -8, -3, 2, 7, 12 });
        System.out.println(ANSI_GREEN + "-- Linked:" + ANSI_RESET);
        System.out.println(ANSI_GREEN + "hashcode: " + ANSI_RESET + funcLink.hashCode());
        System.out.println(funcLink.toString());
        System.out.println("");
        TabulatedFunction funcArr = new LinkedListTabulatedFunction(-2, 2, new double[]{ -8, -3, 2, 7, 12 });
        System.out.println(ANSI_GREEN + "-- Array:" + ANSI_RESET);
        System.out.println(ANSI_GREEN + "hashcode: " + ANSI_RESET + funcArr.hashCode());
        System.out.println(funcArr.toString());
        System.out.println("");

        System.out.println(ANSI_MAGENTA + "___________equality___________" + ANSI_RESET);
        System.out.println(ANSI_GREEN + "cos equals sin: " + ANSI_RESET + sin2.equals(cos2));
        System.out.println(ANSI_GREEN + "cos equals cos: " + ANSI_RESET + cos2.equals(cos2));
        System.out.println(ANSI_GREEN + "cloned cos equals cos: " + ANSI_RESET + clonedCos2.equals(cos2));
        System.out.println(ANSI_GREEN + "linked equals array: " + ANSI_RESET + funcLink.equals(funcArr));
        System.out.println(ANSI_GREEN + "array equals linked: " + ANSI_RESET + funcArr.equals(funcLink));

        System.out.println(ANSI_BLUE+"____LR6___________________________________________________________________________________________"+ANSI_RESET);
        System.out.println(ANSI_MAGENTA + "___________integral___________" + ANSI_RESET);

        Function expFuncForIntegral = new Exp();
        outputFuncWithStep(expFuncForIntegral, -1, 2, 0.5, format);

        double expIntegral = Functions.integrate(expFuncForIntegral, 0, 1, 0.0000009);
        System.out.println(ANSI_GREEN + "exponent integral: " + ANSI_RESET + expIntegral);
    }

    private static void outputFuncWithStep(Function func, double minX, double maxX, double step, DecimalFormat format)
    {
        for (double x = minX; Double.compare(x, maxX) <= 0; x += step) {
            System.out.println(format.format(x) + " | " + format.format(func.getFunctionValue(x)));
        }
    }
}
