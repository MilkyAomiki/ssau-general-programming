package functions;

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
        double step = (rightX - leftX) / pointsCount;

        double current = leftX;
        int i = 0;
        FunctionPoint[] points = new FunctionPoint[pointsCount];
        while (current <= rightX) {
            points[i] = new FunctionPoint(current, function.getFunctionValue(current));

            //переходим на след шаг
            current += step;
            i++;
        }

        return new LinkedListTabulatedFunction(points);
    }
}
