package functions;

public class TabulatedFunction {
    private FunctionPoint[] points;
    private int size = 0;

    public TabulatedFunction(double leftX, double rightX, int pointsCount) {
        double step = (rightX - leftX) / pointsCount;

        points = new FunctionPoint[pointsCount];
        double current = leftX;
        int i = 0;
        while (current <= rightX) {
            points[i] = new FunctionPoint(current, 0);

            current += step;
            i++;
        }
    }

    public TabulatedFunction(double leftX, double rightX, double[] values) {
        double step = (rightX - leftX) / (values.length-1);

        points = new FunctionPoint[values.length];
        double current = leftX;
        int i = 0;
        while (current <= rightX) {
            points[i] = new FunctionPoint(current, values[i]);

            current += step;
            i++;
        }
    }

    public void deletePoint(int index)
    {
        FunctionPoint[] newArr = new FunctionPoint[points.length-1];

        if (index != 0) {
            System.arraycopy(points, 0, newArr, 0, index);
        }

        System.arraycopy(points, index+1, newArr, index, points.length - index-1);

        points = newArr;
    }

    public void addPoint(FunctionPoint point)
    {
        FunctionPoint[] newArr = new FunctionPoint[points.length+1];

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

        if (index != 0) {
            System.arraycopy(points, 0, newArr, 0, index);
        }

        if (index != points.length) {
            System.arraycopy(points, index, newArr, index+1, points.length - index);
        }

        newArr[index] = new FunctionPoint(point);

        points = newArr;
    }

    public double getLeftDomainBorder()
    {
        if (points.length > 0) {
            return getLeftmost().getX();
        }

        return Double.NaN;
    }

    public double getRightDomainBorder()
    {
        if (points.length > 0) {
            return getRightmost().getX();
        }

        return Double.NaN;
    }

    public int getPointsCount()
    {
        return points.length;
    }

    public FunctionPoint getPoint(int index)
    {
        return new FunctionPoint(points[index]);
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
        return points[points.length-1];
    }

    private boolean isXInInterval(int index, double x)
    {
        double leftX = x-1;
        double rightX = x+1;

        if (index > 0) {
            leftX = points[index-1].getX();
        }

        if (index < points.length-1) {
            rightX = points[index+1].getX();
        }

        if (leftX < x && x < rightX) {
            return true;
        }

        return false;
    }

}
