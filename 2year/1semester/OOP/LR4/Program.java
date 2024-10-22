import functions.FunctionPoint;
import functions.FunctionPointIndexOutOfBoundsException;
import functions.InappropriateFunctionPointException;
import functions.LinkedListTabulatedFunction;
import functions.TabulatedFunction;

public class Program {
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
    }
}
