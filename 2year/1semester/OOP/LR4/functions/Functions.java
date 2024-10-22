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
}
