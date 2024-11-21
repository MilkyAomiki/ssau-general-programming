package functions;

import functions.meta.Composition;
import functions.meta.Mult;
import functions.meta.Power;
import functions.meta.Scale;
import functions.meta.Shift;
import functions.meta.Sum;

public final class Functions {
    //not allow creation
    private Functions() {}

    /**
     * возвращает объект функции, полученной из исходной сдвигом вдоль осей 
     * @param f
     * @param shiftX
     * @param shiftY
     * @return
     */
    public static Function shift(Function f, double shiftX, double shiftY)
    {
        return new Shift(f, shiftX, shiftY);
    }

    /**
     * возвращает объект функции, полученной из исходной масштабированием вдоль осей
     * @param f
     * @param scaleX
     * @param scaleY
     * @return
     */
    public static Function scale(Function f, double scaleX, double scaleY)
    {
        return new Scale(f, scaleX, scaleY);
    }

    /**
     * возвращает объект функции, являющейся заданной степенью исходной
     * @param f
     * @param power
     * @return
     */
    public static Function power(Function f, double power)
    {
        return new Power(f, power);
    }

    /**
     * возвращает объект функции, являющейся суммой двух исходных
     * @param f1
     * @param f2
     * @return
     */
    public static Function sum(Function f1, Function f2)
    {
        return new Sum(f1, f2);
    }

    /**
     * возвращает объект функции, являющейся произведением двух исходных
     * @param f1
     * @param f2
     * @return
     */
    public static Function mult(Function f1, Function f2)
    {
        return new Mult(f1, f2);
    }

    /**
     * возвращает объект функции, являющейся композицией двух исходных
     * @param f1
     * @param f2
     * @return
     */
    public static Function composition(Function f1, Function f2)
    {
        return new Composition(f1, f2);
    }

    public static double integrate(Function func, double leftLim, double rightLim, double step)
    {
        if (Double.compare(rightLim, func.getRightDomainBorder()) > 0 ) {
            throw new FunctionPointIndexOutOfBoundsException("Предел интегрирования справа " + rightLim + " выходит за рамки области определения функции " + func.getRightDomainBorder());
        }

        if (Double.compare(leftLim, func.getLeftDomainBorder()) < 0 ) {
            throw new FunctionPointIndexOutOfBoundsException("Предел интегрирования cлева " + leftLim + " выходит за рамки области определения функции " + func.getLeftDomainBorder());
        }

        double integralSum = 0;
        double currRightX = leftLim+step;
        for (; Double.compare(currRightX, rightLim) <= 0; currRightX += step) {
            double leftX = currRightX - step;

            double xLength = currRightX - leftX;
            
            double leftY = func.getFunctionValue(leftX);
            double rightY  = func.getFunctionValue(currRightX);

            integralSum += xLength * (leftY + rightY)/2;
        }

        //добиавем оставшееся
        if (Double.compare(currRightX, rightLim) < 0) {
            double leftX = currRightX;

            double xLength = rightLim - leftX;
            
            double leftY = func.getFunctionValue(leftX);
            double rightY  = func.getFunctionValue(rightLim);

            integralSum += xLength * (leftY + rightY)/2;
        }

        return integralSum;
    }
}
