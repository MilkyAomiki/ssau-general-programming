package functions;

public class TabulatedFunction {
    private FunctionPoint[] points;
    private int size = 0;

    public TabulatedFunction(double leftX, double rightX, int pointsCount) {
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

    public TabulatedFunction(double leftX, double rightX, double[] values) {
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
        System.arraycopy(points, index+1, points, index, getSize() - index-1);
        setSize(getSize()-1);
    }

    public void addPoint(FunctionPoint point)
    {
        //ищем index на который поставить значение
        int index = 0;
        for (; index < points.length; index++) {
            if (isXInInterval(index, point.getX())) {
                //уже есть данный x в таблице, не можем добавить 
                if (points[index].getX() == point.getX()) {
                    return;
                }

                //решаем куда встать - до index или после него
                if (points[index].getX() < point.getX()) {
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
        return points[index];
    }

    public void setPoint(int index, FunctionPoint point)
    {
        if (isXInInterval(index, point.getX())) {
            points[index] = new FunctionPoint(point);
        }
    }

    public double getPointX(int index)
    {
        return points[index].getX();
    }

    public void setPointX(int index, double x)
    {
        if (isXInInterval(index, x)) {
            points[index].setX(x);
        }
    }

    public double getPointY(int index)
    {
        return points[index].getY();
    }

    public void setPointY(int index, double y)
    {
        points[index].setY(y);
    }

    public double getFunctionValue(double x)
    {
        if (x < getLeftDomainBorder() || x > getRightDomainBorder())
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

        if (leftX < x && x < rightX) {
            return true;
        }

        return false;
    }

}
