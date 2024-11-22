package functions;

import java.io.*;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;;

public class TabulatedFunctions  {

    private static TabulatedFunctionFactory tabFuncFactory = new LinkedListTabulatedFunction.LinkedListTabulatedFunctionFactory();

    //not allow creation
    private TabulatedFunctions() {}
    
    public static void setTabulatedFunctionFactory(TabulatedFunctionFactory factory)
    {
        tabFuncFactory = factory;
    }
    
    public static TabulatedFunction createTabulatedFunction(FunctionPoint[] points)
    {
        return tabFuncFactory.createTabulatedFunction(points);
    }

    public static TabulatedFunction createTabulatedFunction(double leftX, double rightX, int pointsCount)
    {
        return tabFuncFactory.createTabulatedFunction(leftX, rightX, pointsCount);
    }

    public static TabulatedFunction createTabulatedFunction(double leftX, double rightX, double[] values)
    {
        return tabFuncFactory.createTabulatedFunction(leftX, rightX, values);
    }
    
    public static TabulatedFunction createTabulatedFunction(FunctionPoint[] points, Class<? extends TabulatedFunction> tabFuncClass)
    {
        try {
            Constructor<? extends TabulatedFunction> constructor = tabFuncClass.getConstructor(points.getClass());
            return constructor.newInstance((Object)points);
        } catch (NoSuchMethodException | IllegalAccessException | InstantiationException | InvocationTargetException e) {
            throw new IllegalArgumentException(e);
        }
    }

    public static TabulatedFunction createTabulatedFunction(double leftX, double rightX, int pointsCount, Class<? extends TabulatedFunction> tabFuncClass)
    {
        try {
            Constructor<? extends TabulatedFunction> constructor = tabFuncClass.getConstructor(double.class, double.class, int.class);
            return constructor.newInstance(leftX, rightX, pointsCount);
        } catch (NoSuchMethodException | IllegalAccessException | InstantiationException | InvocationTargetException e) {
            throw new IllegalArgumentException(e);
        }
    }

    public static TabulatedFunction createTabulatedFunction(double leftX, double rightX, double[] values, Class<? extends TabulatedFunction> tabFuncClass)
    {
        try {
            Constructor<? extends TabulatedFunction> constructor = tabFuncClass.getConstructor(double.class, double.class, double[].class);
            return constructor.newInstance(leftX, rightX, values);
        } catch (NoSuchMethodException | IllegalAccessException | InstantiationException | InvocationTargetException e) {
            throw new IllegalArgumentException(e);
        }
    }

    /**
     * получает функцию и возвращает её табулированный аналог на заданном отрезке с заданным количеством точек
     * @param function
     * @param leftX
     * @param rightX
     * @param pointsCount
     * @return
     * @throws IllegalArgumentException
     */
    public static TabulatedFunction tabulate(Function function, double leftX, double rightX, int pointsCount) throws IllegalArgumentException
    {
        if (Double.compare(leftX, function.getLeftDomainBorder()) < 0)
            throw new IllegalArgumentException("provided left border " + leftX + " is less than function border " + function.getLeftDomainBorder());       

        if (Double.compare(rightX, function.getRightDomainBorder()) > 0)
            throw new IllegalArgumentException("provided right border " + rightX + " is greater than function border " + function.getRightDomainBorder());       

        //получаем значения Y
        double step = (rightX - leftX) / (pointsCount-1);

        double current = leftX;
        int i = 0;
        FunctionPoint[] points = new FunctionPoint[pointsCount];
        while (Double.compare(current, rightX) <= 0) {
            points[i] = new FunctionPoint(current, function.getFunctionValue(current));

            //переходим на след шаг
            current += step;
            i++;
        }

        return createTabulatedFunction(points);
    }

    /**
     * получает функцию и возвращает её табулированный аналог на заданном отрезке с заданным количеством точек
     * @param function
     * @param leftX
     * @param rightX
     * @param pointsCount
     * @return
     * @throws IllegalArgumentException
     */
    public static TabulatedFunction tabulate(Function function, double leftX, double rightX, int pointsCount, Class<? extends TabulatedFunction> tabFuncClass) throws IllegalArgumentException
    {
        if (Double.compare(leftX, function.getLeftDomainBorder()) < 0)
            throw new IllegalArgumentException("provided left border " + leftX + " is less than function border " + function.getLeftDomainBorder());       

        if (Double.compare(rightX, function.getRightDomainBorder()) > 0)
            throw new IllegalArgumentException("provided right border " + rightX + " is greater than function border " + function.getRightDomainBorder());       

        //получаем значения Y
        double step = (rightX - leftX) / (pointsCount-1);

        double current = leftX;
        int i = 0;
        FunctionPoint[] points = new FunctionPoint[pointsCount];
        while (Double.compare(current, rightX) <= 0) {
            points[i] = new FunctionPoint(current, function.getFunctionValue(current));

            //переходим на след шаг
            current += step;
            i++;
        }

        return createTabulatedFunction(points, tabFuncClass);
    }

    /**
     * Вводит значения функции в поток
     * @param function
     * @param out
     * @throws IOException if an I/O error occurs
     */
    public static void outputTabulatedFunction(TabulatedFunction function, OutputStream out) throws IOException
    {
        DataOutputStream dataout = new DataOutputStream(out);
        
        dataout.writeInt(function.getPointsCount());

        for (int i = 0; i < function.getPointsCount(); i++) {
            FunctionPoint point = function.getPoint(i);

            dataout.writeDouble(point.getX());
            dataout.writeDouble(point.getY());
        }
    }

    /**
     * Читает функцию из потока
     * @param in
     * @return
     * @throws IOException if an I/O error occurs
     */
    public static TabulatedFunction inputTabulatedFunction(InputStream in) throws IOException
    {
        DataInputStream datain = new DataInputStream(in);
        
        int pointsCount =  datain.readInt();
        FunctionPoint[] points = new FunctionPoint[pointsCount];

        for (int i = 0; i < pointsCount; i++) {
            double xVal = datain.readDouble();
            double yVal = datain.readDouble();

            points[i] = new FunctionPoint(xVal, yVal);
        }

        return createTabulatedFunction(points);
    }

    /**
     * Читает функцию из потока
     * @param in
     * @return
     * @throws IOException if an I/O error occurs
     */
    public static TabulatedFunction inputTabulatedFunction(InputStream in, Class<? extends TabulatedFunction> tabFuncClass) throws IOException
    {
        DataInputStream datain = new DataInputStream(in);
        
        int pointsCount =  datain.readInt();
        FunctionPoint[] points = new FunctionPoint[pointsCount];

        for (int i = 0; i < pointsCount; i++) {
            double xVal = datain.readDouble();
            double yVal = datain.readDouble();

            points[i] = new FunctionPoint(xVal, yVal);
        }

        return createTabulatedFunction(points, tabFuncClass);
    }
    
    /**
     * Записывает функцию в виде строки в out
     * @param function
     * @param out
     * @throws IOException if an I/O error occurs
     */
    public static void writeTabulatedFunction(TabulatedFunction function, Writer out) throws IOException
    {
        out.write(Integer.toString(function.getPointsCount()));

        for (int i = 0; i < function.getPointsCount(); i++) {
            FunctionPoint point = function.getPoint(i);

            out.write("\n" + point.getX() + " " + point.getY());
        }
    }

    /**
     * Читает функцию из строки in
     * @param in
     * @return
     * @throws IOException if an I/O error occurs
     */
    public static TabulatedFunction readTabulatedFunction(Reader in) throws IOException
    {
        StreamTokenizer tokens = new StreamTokenizer(in);

        tokens.nextToken();
        int pointsCount = (int)tokens.nval;

        FunctionPoint[] points = new FunctionPoint[pointsCount];

        for (int i = 0; i < pointsCount; i++) {
            
            tokens.nextToken();
            double xVal = tokens.nval;

            tokens.nextToken();
            double yVal = tokens.nval;

            points[i] = new FunctionPoint(xVal, yVal);
        }

        return createTabulatedFunction(points);
    }

    /**
     * Читает функцию из строки in
     * @param in
     * @return
     * @throws IOException if an I/O error occurs
     */
    public static TabulatedFunction readTabulatedFunction(Reader in, Class<? extends TabulatedFunction> tabFuncClass) throws IOException
    {
        StreamTokenizer tokens = new StreamTokenizer(in);

        tokens.nextToken();
        int pointsCount = (int)tokens.nval;

        FunctionPoint[] points = new FunctionPoint[pointsCount];

        for (int i = 0; i < pointsCount; i++) {
            
            tokens.nextToken();
            double xVal = tokens.nval;

            tokens.nextToken();
            double yVal = tokens.nval;

            points[i] = new FunctionPoint(xVal, yVal);
        }

        return createTabulatedFunction(points, tabFuncClass);
    }
}
