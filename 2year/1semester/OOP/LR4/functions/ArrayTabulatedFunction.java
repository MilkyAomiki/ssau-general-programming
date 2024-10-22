package functions;

public class ArrayTabulatedFunction implements TabulatedFunction {
    private FunctionPoint[] points;
    private int size = 0;

    public ArrayTabulatedFunction(double leftX, double rightX, int pointsCount) {
        if (leftX >= rightX) {
            throw new IllegalArgumentException("Left border (" + leftX +") should be smaller than the right one (" + rightX + ")");
        }

        if (pointsCount < 2) {
            throw new IllegalArgumentException("The number of points should not be less than 2");
        }

        double step = (rightX - leftX) / pointsCount;
        
        setSize(pointsCount);
        points = new FunctionPoint[getSize()*2];

        //заполняем points
        double current = leftX;
        int i = 0;
        while (current <= rightX) {
            points[i] = new FunctionPoint(current, 0);

            //переходим на след шаг
            current += step;
            i++;
        }
    }

    public ArrayTabulatedFunction(double leftX, double rightX, double[] values) {
        if (leftX >= rightX) {
            throw new IllegalArgumentException("Left border (" + leftX +") should be smaller than the right one (" + rightX + ")");
        }

        if (values.length < 2) {
            throw new IllegalArgumentException("The number of points should not be less than 2");
        }

        double step = (rightX - leftX) / (values.length-1);
        
        setSize(values.length);
        points = new FunctionPoint[getSize() * 2];

        //заполняем points
        double current = leftX;
        int i = 0;
        while (current <= rightX) {
            points[i] = new FunctionPoint(current, values[i]);

            //переходим на след шаг
            current += step;
            i++;
        }
    }

    private int getSize()
    {
        return size;
    }

    private void setSize(int s)
    {
        size = s;
    }

    /**
     * Расширение массива points в два раза
     */
    private void resize()
    {
        FunctionPoint[] newArr = new FunctionPoint[points.length*2];
        System.arraycopy(points, 0, newArr, 0, points.length);
        points = newArr;
    }

    public void deletePoint(int index)
    {
        if (index < 0 || index >= getSize())
            throw new FunctionPointIndexOutOfBoundsException("Index " + index + " is out of bounds (0 -" + getSize() + ")");

        if (getSize() < 3)
            throw new IllegalStateException("Size after deletion is less than 3");

        System.arraycopy(points, index+1, points, index, getSize() - index-1);
        setSize(getSize()-1);
    }

    public void addPoint(FunctionPoint point) throws InappropriateFunctionPointException
    {
        //ищем index на который поставить значение
        int index = 0;
        for (; index < points.length; index++) {
            if (isXInInterval(index, point.getX())) {
                //уже есть данный x в таблице, не можем добавить 
                if (Double.compare(points[index].getX(), point.getX()) == 0) {
                    throw new InappropriateFunctionPointException("Given value of x " + point.getX() + " already exists with value " + points[index].getY());
                }

                //решаем куда встать - до index или после него
                if (Double.compare(points[index].getX(), point.getX()) < 0) {
                    index++;
                }

                break;
            }
        }

        if (getSize()+1 == points.length) {
            resize();
        }

       //сдвигаем значения чтобы освободить ячейку 
        if (index != getSize()) {
            System.arraycopy(points, index, points, index+1, getSize() - index);
        }

        points[index] = new FunctionPoint(point);
        setSize(getSize()+1);
    }

    public double getLeftDomainBorder()
    {
        if (getSize() > 0) {
            return getLeftmost().getX();
        }

        return Double.NaN;
    }

    public double getRightDomainBorder()
    {
        if (getSize() > 0) {
            return getRightmost().getX();
        }

        return Double.NaN;
    }

    public int getPointsCount()
    {
        return getSize();
    }

    public FunctionPoint getPoint(int index)
    {
        if (index < 0 || index >= getSize()) {
            throw new FunctionPointIndexOutOfBoundsException("Index " + index + " is out of bounds (0 -" + getSize() + ")");
        }

        return points[index];
    }

    public void setPoint(int index, FunctionPoint point) throws InappropriateFunctionPointException
    {
        if (index < 0 || index >= getSize()) {
            throw new FunctionPointIndexOutOfBoundsException("Index " + index + " is out of bounds (0 -" + getSize() + ")");
        }

        if (isXInInterval(index, point.getX()))
            points[index] = new FunctionPoint(point);
        else
            throw new InappropriateFunctionPointException("Provided value of x " + point.getX() + " is out of bounds at index " + index);
    }

    public double getPointX(int index)
    {
        if (index < 0 || index >= getSize()) {
            throw new FunctionPointIndexOutOfBoundsException("Index " + index + " is out of bounds (0 -" + getSize() + ")");
        }

        return points[index].getX();
    }

    public void setPointX(int index, double x) throws InappropriateFunctionPointException
    {
        if (index < 0 || index >= getSize()) {
            throw new FunctionPointIndexOutOfBoundsException("Index " + index + " is out of bounds (0 -" + getSize() + ")");
        }

        if (isXInInterval(index, x))
            points[index].setX(x);
        else
            throw new InappropriateFunctionPointException("Provided value of x " + x + " is out of bounds at index " + index);
    }

    public double getPointY(int index)
    {
        if (index < 0 || index >= getSize()) {
            throw new FunctionPointIndexOutOfBoundsException("Index " + index + " is out of bounds (0 -" + getSize() + ")");
        }

        return points[index].getY();
    }

    public void setPointY(int index, double y)
    {
        if (index < 0 || index >= getSize()) {
            throw new FunctionPointIndexOutOfBoundsException("Index " + index + " is out of bounds (0 -" + getSize() + ")");
        }

        points[index].setY(y);
    }

    public double getFunctionValue(double x)
    {
        if (Double.compare(x, getLeftDomainBorder()) < 0 || Double.compare(x, getRightDomainBorder()) > 0)
            return Double.NaN;

        //линейная интерполяция
        double x2 = getRightmost().getX();
        double y2 = getRightmost().getY();

        double x1 = getLeftmost().getX();
        double y1 = getLeftmost().getY();

        double y = (y2-y1)*(x-x1)/(x2-x1) + y1;

        return y;
    }

    private FunctionPoint getLeftmost()
    {
        return points[0];
    }

    private FunctionPoint getRightmost()
    {
        return points[getSize()-1];
    }

    /**
     * Проверяет является ли данный x, на данном y, в массиве points, больше левого значения и меньше правого
     * @param index индекс в массиве points
     * @param x 
     * @return
     */
    private boolean isXInInterval(int index, double x)
    {
        //значения по умолчанию всегда дают true
        double leftX = x-1;
        double rightX = x+1;

        //если есть левая граница - ставим ее
        if (index > 0) {
            leftX = points[index-1].getX();
        }

        //если есть правая граница - ставим ее
        if (index < getSize()-1) {
            rightX = points[index+1].getX();
        }

        if (Double.compare(leftX, x) < 0 && Double.compare(x, rightX) < 0) {
            return true;
        }

        return false;
    }

}
