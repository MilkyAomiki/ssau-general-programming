package functions;

public class TabulatedFunction {
    private FunctionPoint[] points;
    private int size = 0;

    public TabulatedFunction(double leftX, double rightX, int pointsCount) {
        if (leftX >= rightX) {
            throw new IllegalArgumentException("Left border should be smaller than the right one");
        }

        if (pointsCount < 2) {
            throw new IllegalArgumentException("The number of points should not be less than 2");
        }

        double step = (rightX - leftX) / pointsCount;
        
        setSize(pointsCount);
        points = new FunctionPoint[getSize()*2];
        double current = leftX;
        int i = 0;
        while (current <= rightX) {
            points[i] = new FunctionPoint(current, 0);

            current += step;
            i++;
        }
    }

    public TabulatedFunction(double leftX, double rightX, double[] values) {
        if (leftX >= rightX) {
            throw new IllegalArgumentException("Left border should be smaller than the right one");
        }

        if (values.length < 2) {
            throw new IllegalArgumentException("The number of points should not be less than 2");
        }

        double step = (rightX - leftX) / (values.length-1);
        
        setSize(values.length);
        points = new FunctionPoint[getSize() * 2];
        double current = leftX;
        int i = 0;
        while (current <= rightX) {
            points[i] = new FunctionPoint(current, values[i]);

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

    private void resize()
    {
        FunctionPoint[] newArr = new FunctionPoint[points.length*2];
        System.arraycopy(points, 0, newArr, 0, points.length);
        points = newArr;
    }

    public void deletePoint(int index)
    {
        if (index < 0 || index >= getSize()) {
            throw new FunctionPointIndexOutOfBoundsException();
        }

        System.arraycopy(points, index+1, points, index, getSize() - index-1);
        setSize(getSize()-1);
    }

    public void addPoint(FunctionPoint point)
    {
        int index = 0;
        for (; index < points.length; index++) {
            if (isXInInterval(index, point.getX())) {
                if (points[index].getX() == point.getX()) {
                    return;
                }

                if (points[index].getX() < point.getX()) {
                    index++;
                }

                break;
            }
        }

        if (getSize()+1 == points.length) {
            resize();
        }

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
            throw new FunctionPointIndexOutOfBoundsException();
        }

        return new FunctionPoint(points[index]);
    }

    public void setPoint(int index, FunctionPoint point)
    {
        if (index < 0 || index >= getSize()) {
            throw new FunctionPointIndexOutOfBoundsException();
        }

        if (isXInInterval(index, point.getX())) {
            points[index] = new FunctionPoint(point);
        }
    }

    public double getPointX(int index)
    {
        if (index < 0 || index >= getSize()) {
            throw new FunctionPointIndexOutOfBoundsException();
        }

        return points[index].getX();
    }

    public void setPointX(int index, double x)
    {
        if (index < 0 || index >= getSize()) {
            throw new FunctionPointIndexOutOfBoundsException();
        }

        if (isXInInterval(index, x)) {
            points[index].setX(x);
        }
        else
        {
            throw new InappropriateFunctionPointException();
        }
    }

    public double getPointY(int index)
    {
        if (index < 0 || index >= getSize()) {
            throw new FunctionPointIndexOutOfBoundsException();
        }

        return points[index].getY();
    }

    public void setPointY(int index, double y)
    {
        if (index < 0 || index >= getSize()) {
            throw new FunctionPointIndexOutOfBoundsException();
        }

        points[index].setY(y);
    }

    public double getFunctionValue(double x)
    {
        if (x < getLeftDomainBorder() || x > getRightDomainBorder())
            return Double.NaN;

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

    private boolean isXInInterval(int index, double x)
    {
        double leftX = x-1;
        double rightX = x+1;

        if (index > 0) {
            leftX = points[index-1].getX();
        }

        if (index < getSize()-1) {
            rightX = points[index+1].getX();
        }

        if (leftX < x && x < rightX) {
            return true;
        }

        return false;
    }

}
