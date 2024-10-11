package functions;

public class FunctionNode {
    private FunctionNode next;
    private FunctionNode prev;

    private FunctionPoint data;

    public FunctionNode(FunctionNode next, FunctionNode prev, FunctionPoint data) {
        this.next = next;
        this.prev = prev;
        this.data = data;
    }

    public FunctionPoint getData() {
        return data;
    }

    public void setData(FunctionPoint data) {
        this.data = data;
    }

    public FunctionNode getPrev() {
        return prev;
    }

    public void setPrev(FunctionNode prev) {
        this.prev = prev;
    }

    public FunctionNode getNext() {
        return next;
    }

    public void setNext(FunctionNode next) {
        this.next = next;
    }
}
