import functions.FunctionPoint;
import functions.TabulatedFunction;

public class Program {
    public static void main(String[] args) {
        TabulatedFunction tabFuncLin = new TabulatedFunction(-2, 2, new double[]{ -8, -3, 2, 7, 12 });
        
        
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

        TabulatedFunction tabFunc = new TabulatedFunction(-3, 3, new double[]{ -54, -2, 2, 54 });
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
        tabFunc.addPoint(new FunctionPoint(0, 0));

        tabFunc.deletePoint(2);
        tabFunc.addPoint(new FunctionPoint(2, 16));


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
    }
}
