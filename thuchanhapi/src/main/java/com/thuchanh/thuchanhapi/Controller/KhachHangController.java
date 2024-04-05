package com.thuchanh.thuchanhapi.Controller;

import com.thuchanh.thuchanhapi.Entity.KhachHang;
import com.thuchanh.thuchanhapi.Service.KhachhangService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api/v1/khachhang")
public class KhachHangController {
    @Autowired
    KhachhangService khachhangService;
    @GetMapping
    public ResponseEntity<?> getAllKhachHang(){
        return new ResponseEntity<>(khachhangService.getAllKhachHang(), HttpStatus.OK);
    }

    @GetMapping("/{tenKhachHang}")
    public ResponseEntity<?> getAllKhachHangByTen(@PathVariable String tenKhachHang){
        try{
            return new ResponseEntity<>(khachhangService.getAllKhachHangByTen(tenKhachHang), HttpStatus.OK);
        }
        catch (Exception e){
            return new ResponseEntity<>(e.getMessage(), HttpStatus.NOT_FOUND);
        }
    }

    @PostMapping
    public ResponseEntity<?> addKhachHang(@RequestBody KhachHang khachhang){
        return new ResponseEntity<>(khachhangService.addKhachHang(khachhang), HttpStatus.CREATED);
    }

    @PutMapping("/{khachHangId}")
    public ResponseEntity<?> updateKhachHang(@PathVariable Long khachHangId, @RequestBody KhachHang khachhang){
        try{
            return new ResponseEntity<>(khachhangService.updateKhachHang(khachHangId, khachhang), HttpStatus.OK);
        }
        catch (Exception e){
            return new ResponseEntity<>(e.getMessage(), HttpStatus.NOT_FOUND);
        }
    }

    @DeleteMapping("/{khachHangId}")
    public ResponseEntity<?> deleteKhachHang(@PathVariable Long khachHangId){
        try{
            return new ResponseEntity<>(khachhangService.deleteKhachHang(khachHangId, null), HttpStatus.OK);
        }
        catch (Exception e){
            return new ResponseEntity<>(e.getMessage(), HttpStatus.NOT_FOUND);
        }
    }

}
