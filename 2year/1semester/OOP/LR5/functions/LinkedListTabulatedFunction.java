package functions;

import java.io.Externalizable;
import java.io.IOException;
import java.io.ObjectInput;
import java.io.ObjectOutput;
import java.util.Arrays;

public class LinkedListTabulatedFunction implements TabulatedFunction, Externalizable {
    private FunctionNode head;
    private FunctionNode lastAccessedNode;
    private int lastAccessedIndex = 0;

    private int size = 0;

    //For externalizable
    public LinkedListTabulatedFunction() {

    }

    public LinkedListTabulatedFunction(FunctionPoint[] points) {
        if (points.length < 2) {
            throw new IllegalArgumentException("The number of points should not be less than 2");
        }

        //проверяем порядок
        for (int i = 1; i < points.length; i++) {
            if (Double.compare(points[i-1].getX(), points[i].getX()) > 0) {

                //собираем числа до текущих в строку
                String values = "";
                for (int j = 0; j <= i; j++) 
                    values += points[j].getX() + ", ";

                values += "...";

                throw new IllegalArgumentException("X values are out of order: "+ values);
            }
        }

        initHead();

        for (int i = 0; i < points.length; i++)
            addNodeToTail(points[i]);

        size = points.length;
    }

    public LinkedListTabulatedFunction(double leftX, double rightX, int pointsCount) {
        if (Double.compare(leftX, rightX) >= 0) {
            throw new IllegalArgumentException("Left border (" + leftX +") should be smaller than the right one (" + rightX + ")");
        }

        if (pointsCount < 2) {
            throw new IllegalArgumentException("The number of points should not be less than 2");
        }

        initHead();

        double step = (rightX - leftX) / (pointsCount - 1);
        
        setSize(pointsCount);

        //заполняем points
        double current = leftX;
        FunctionNode currNode = head;
        while (current <= rightX) {
            currNode.setNext(new FunctionNode(head, currNode, new FunctionPoint(current, 0)));
            currNode.getNext().setPrev(currNode);
            head.setPrev(currNode.getNext());

            //переходим на след шаг
            current += step;
            currNode = currNode.getNext();
        }
    }

    public LinkedListTabulatedFunction(double leftX, double rightX, double[] values) {
        if (Double.compare(leftX, rightX) >= 0) {
            throw new IllegalArgumentException("Left border (" + leftX +") should be smaller than the right one (" + rightX + ")");
        }

        if (values.length < 2) {
            throw new IllegalArgumentException("The number of points should not be less than 2");
        }

        initHead();

        double step = (rightX - leftX) / (values.length - 1);
        
        setSize(values.length);

        //заполняем points
        double current = leftX;
        FunctionNode currNode = head;
        int i = 0;
        while (Double.compare(current, rightX) <= 0) {
            currNode.setNext(new FunctionNode(head, currNode, new FunctionPoint(current, values[i])));
            currNode.getNext().setPrev(currNode);
            head.setPrev(currNode.getNext());

            //переходим на след шаг
            current += step;
            i++;
            currNode = currNode.getNext();
        }
    }

    private void initHead()
    {
        head = new FunctionNode(null, null, null);
        head.setNext(head);
        head.setPrev(head);
        lastAccessedNode = head;
    }

    private int getSize()
    {
        return size;
    }

    private void setSize(int s)
    {
        size = s;
    }

    public void deletePoint(int index)
    {
        deleteNodeByIndex(index);
    }

    public void addPoint(FunctionPoint point) throws InappropriateFunctionPointException
    {
        //ищем index на который поставить значение
        FunctionNode curr = head.getNext();
        while (curr != head) {
            if (isXInInterval(curr, point.getX())) {
                //уже есть данный x в таблице, не можем добавить 
                if (Double.compare(curr.getData().getX(), point.getX()) == 0) {
                    throw new InappropriateFunctionPointException("Given value of x " + point.getX() + " already exists with value " + curr.getData().getY());
                }

                //решаем куда встать - до index или после него
                if (Double.compare(curr.getData().getX(), point.getX()) < 0) {
                    curr = curr.getNext();
                }

                break;
            }

            curr = curr.getNext();
        }

        FunctionNode new_left = curr.getPrev();
        FunctionNode new_el = new FunctionNode(curr, new_left, point);
        new_left.setNext(new_el);
        curr.setPrev(new_el);

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

    private FunctionNode getNodeByIndex(int index)
    {
        if (index < 0 || index >= getSize()) {
            throw new FunctionPointIndexOutOfBoundsException("Index " + index + " is out of bounds (0 -" + getSize() + ")");
        }

        FunctionNode curr = head.getNext();
        boolean forward = true;
        int i = 0;
        //optimizations
        //1. for distance from last accessed node
        if (Math.abs(index - lastAccessedIndex) < index) {
            if (index > lastAccessedIndex) {
                forward = true;
            }
            else {
                forward = false;
            }
            i = lastAccessedIndex;
            curr = lastAccessedNode;
        }
        //2. for distance from 0
        else
        {
            if (index <= getSize()/2) {
                forward = true;
            }
            else {
                forward = false;
            }
        }

        while (Math.abs(i) != index) {
            if (forward)
            {
                curr = curr.getNext();
                i++;
            }
            else
            {
                curr = curr.getPrev();
                i--;
            }
        }

        lastAccessedIndex = index;
        lastAccessedNode = curr;

        return curr;
    }

    private FunctionNode addNodeToTail(FunctionPoint point)
    {
        FunctionNode left = head.getPrev();
        FunctionNode curr = new FunctionNode(head, left, point);
        left.setNext(curr);
        head.setPrev(curr);

        setSize(getSize()+1);
        return curr;
    }

    private FunctionNode addNodeByIndex(int index)
    {
        FunctionNode curr = getNodeByIndex(index);

        FunctionNode new_left = curr.getPrev();
        FunctionNode new_el = new FunctionNode(curr, new_left, null);
        new_left.setNext(new_el);
        curr.setPrev(new_el);

        //curr moved forward
        if (lastAccessedNode == curr) {
            lastAccessedIndex++;
        }

        setSize(getSize()+1);

        return new_el;
    }

    private FunctionNode deleteNodeByIndex(int index)
    {
        if (index < 0 || index >= getSize())
            throw new FunctionPointIndexOutOfBoundsException("Index " + index + " is out of bounds (0 -" + getSize() + ")");

        if (getSize() < 3)
            throw new IllegalStateException("Size after deletion is less than 3");

        FunctionNode curr = getNodeByIndex(index);
        FunctionNode left = curr.getPrev();
        FunctionNode right = curr.getNext();
        left.setNext(right);
        right.setPrev(left);

        //right replaced curr
        if (lastAccessedNode == curr) {
            lastAccessedNode = right;
        }

        setSize(getSize()-1);

        return curr;
    }

    public FunctionPoint getPoint(int index)
    {
        return getNodeByIndex(index).getData();
    }

    public void setPoint(int index, FunctionPoint point) throws InappropriateFunctionPointException
    {
        if (index < 0 || index >= getSize()) {
            throw new FunctionPointIndexOutOfBoundsException("Index " + index + " is out of bounds (0 -" + getSize() + ")");
        }
        
        FunctionNode curr = getNodeByIndex(index);
        if (isXInInterval(curr, point.getX()))
            curr.setData(new FunctionPoint(point));
        else
            throw new InappropriateFunctionPointException("Provided value of x " + point.getX() + " is out of bounds at index " + index);
    }

    public double getPointX(int index)
    {
        return getPoint(index).getX();
    }

    public void setPointX(int index, double x) throws InappropriateFunctionPointException
    {
        if (index < 0 || index >= getSize()) {
            throw new FunctionPointIndexOutOfBoundsException("Index " + index + " is out of bounds (0 -" + getSize() + ")");
        }

        FunctionNode curr = getNodeByIndex(index);
        if (isXInInterval(curr, x))
            curr.getData().setX(x);
        else
            throw new InappropriateFunctionPointException("Provided value of x " + x + " is out of bounds at index " + index);
    }

    public double getPointY(int index)
    {
        if (index < 0 || index >= getSize()) {
            throw new FunctionPointIndexOutOfBoundsException("Index " + index + " is out of bounds (0 -" + getSize() + ")");
        }

        return getNodeByIndex(index).getData().getY();
    }

    public void setPointY(int index, double y)
    {
        if (index < 0 || index >= getSize()) {
            throw new FunctionPointIndexOutOfBoundsException("Index " + index + " is out of bounds (0 -" + getSize() + ")");
        }

        getNodeByIndex(index).getData().setY(y);
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
        return head.getNext().getData();
    }

    private FunctionPoint getRightmost()
    {
        return head.getPrev().getData();
    }

    /**
     * Проверяет является ли данный x, на данном y, в массиве points, больше левого значения и меньше правого
     * @param index индекс в массиве points
     * @param x 
     * @return
     */
    private boolean isXInInterval(FunctionNode position, double x)
    {
        //значения по умолчанию всегда дают true
        double leftX = x-1;
        double rightX = x+1;

        //если есть левая граница - ставим ее
        if (position.getPrev() != head) {
            leftX = position.getPrev().getData().getX();
        }

        //если есть правая граница - ставим ее
        if (position.getNext() != head) {
            rightX = position.getNext().getData().getX();
        }

        if (Double.compare(leftX, x) < 0 && Double.compare(x, rightX) < 0) {
            return true;
        }

        return false;
    }

    @Override
    public void writeExternal(ObjectOutput out) throws IOException {
        out.writeObject(head);
        out.writeObject(lastAccessedNode);
        out.writeInt(lastAccessedIndex);
        out.writeInt(size);
    }

    @Override
    public void readExternal(ObjectInput in) throws IOException, ClassNotFoundException {
        head = (FunctionNode)in.readObject();
        lastAccessedNode = (FunctionNode)in.readObject();
        lastAccessedIndex = in.readInt();
        size = in.readInt();
    }

    @Override
    public String toString() {
        FunctionNode curr = head.getNext();

        String res = "{" + curr.getData().toString();

        for (int i = 1; i < size; i++) {
            curr = curr.getNext();

            res += ", " + curr.toString();
        }

        res += "}";

        return res;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + ((head == null) ? 0 : head.hashCode());
        
        FunctionNode curr = head.getNext();
        while (curr != head) {
            result = prime * result + curr.getData().hashCode();
        }

        result = prime * result + size;
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj instanceof TabulatedFunction)
        {
            TabulatedFunction other = (TabulatedFunction) obj;

            if (size != other.getPointsCount())
                return false;

            if (other instanceof LinkedListTabulatedFunction) {
                FunctionNode curr = head;
                FunctionNode currOther = ((LinkedListTabulatedFunction)other).head;
                for (int i = 0; i < other.getPointsCount(); i++) {
                    curr = curr.getNext();
    
                    if (!curr.getData().equals(currOther.getData())) {
                        return false;
                    }
                }
            }

            FunctionNode curr = head;
            for (int i = 0; i < other.getPointsCount(); i++) {
                curr = curr.getNext();

                if (!curr.getData().equals(other.getPoint(i))) {
                    return false;
                }
            }
            return true;

        }

        return false;
    }

    @Override
    protected Object clone() {
        LinkedListTabulatedFunction tabFunc = new LinkedListTabulatedFunction();
        tabFunc.initHead();

        FunctionNode curr = head;
        for (int i = 0; i < size; i++) {
            curr = head.getPrev();
            tabFunc.addNodeToTail((FunctionPoint)curr.getData().clone());
        }

        tabFunc.lastAccessedIndex = lastAccessedIndex;
        tabFunc.lastAccessedNode = lastAccessedNode;

        return tabFunc;
    }
}
