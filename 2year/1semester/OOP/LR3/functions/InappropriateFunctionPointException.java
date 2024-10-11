package functions;

/**
 * Выбрасывается при попытке добавления или изменения точки функции несоответствующим образом
 */
public class InappropriateFunctionPointException extends Exception {
    public InappropriateFunctionPointException() {
        super();
    }

    public InappropriateFunctionPointException(String message) {
        super(message);    
    }
    
}