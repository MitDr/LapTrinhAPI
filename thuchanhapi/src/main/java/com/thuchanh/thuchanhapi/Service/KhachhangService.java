package com.thuchanh.thuchanhapi.Service;

import com.thuchanh.thuchanhapi.Entity.KhachHang;

import java.util.List;

public interface KhachhangService {
    public List<KhachHang> getAllKhachHang();
    public List<KhachHang> getAllKhachHangByTen(String tenKhachHang);
    public KhachHang addKhachHang(KhachHang khachhang);
    public KhachHang updateKhachHang(long khachHangId, KhachHang khachhang);
    public KhachHang deleteKhachHang(long khachHangId ,KhachHang khachHang);
}
