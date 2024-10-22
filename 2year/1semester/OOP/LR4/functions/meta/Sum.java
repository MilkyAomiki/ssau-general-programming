package functions.meta;

import functions.Function;

public class Sum implements Function {
    private Function funcLeft;
    private Function funcRight;

    private double leftDomainBorder;
    private double rightDomainBorder;

    public Sum(Function funcLeft, Function funcRight) {
        this.funcLeft = funcLeft;
        this.funcRight = funcRight;

        int leftBorderComparison = Double.compare(funcLeft.getLeftDomainBorder(), funcRight.getLeftDomainBorder());
        leftDomainBorder = leftBorderComparison == 0 || leftBorderComparison < 0? funcLeft.getLeftDomainBorder() : funcRight.getRightDomainBorder();

        int rightBorderComparison = Double.compare(funcLeft.getRightDomainBorder(), funcRight.getRightDomainBorder());
        rightDomainBorder = rightBorderComparison == 0 || leftBorderComparison < 0? funcLeft.getRightDomainBorder() : funcRight.getRightDomainBorder();
    }

    @Override
    public double getLeftDomainBorder() {
        return leftDomainBorder;
    }

    @Override
    public double getRightDomainBorder() {
        return rightDomainBorder;
    }

    @Override
    public double getFunctionValue(double x) {
        return funcLeft.getFunctionValue(x) + funcRight.getFunctionValue(x);
    }
}
