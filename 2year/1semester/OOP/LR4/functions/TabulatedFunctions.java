package functions;

import java.io.*;;

public class TabulatedFunctions  {
    //not allow creation
    private TabulatedFunctions() {}
    
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

        return new ArrayTabulatedFunction(points);
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

        return new ArrayTabulatedFunction(points);
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

        return new ArrayTabulatedFunction(points);
    }
}
