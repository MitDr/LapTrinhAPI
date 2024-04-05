package com.thuchanh.thuchanhapi.Exception;

public class DatExistException extends RuntimeException{
    public DatExistException(String message) {
        super(message);
    }
}
