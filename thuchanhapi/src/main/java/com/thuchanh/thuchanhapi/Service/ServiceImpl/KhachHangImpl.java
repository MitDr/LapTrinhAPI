package com.thuchanh.thuchanhapi.Service.ServiceImpl;

import com.thuchanh.thuchanhapi.Entity.KhachHang;
import com.thuchanh.thuchanhapi.Exception.DataNotFoundException;
import com.thuchanh.thuchanhapi.Repository.KhachHangRepository;
import com.thuchanh.thuchanhapi.Service.KhachhangService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class KhachHangImpl implements KhachhangService {
    @Autowired
    KhachHangRepository khachHangRepository;
    @Override
    public List<KhachHang> getAllKhachHang() {
        return khachHangRepository.findAll();
    }

    @Override
    public List<KhachHang> getAllKhachHangByTen(String tenKhachHang) {
        return khachHangRepository.findBytenKhachHangContaining(tenKhachHang);
    }

    @Override
    public KhachHang addKhachHang(KhachHang khachhang) {
        return khachHangRepository.save(khachhang);
    }

    @Override
    public KhachHang updateKhachHang(long khachHangId, KhachHang khachhang) {
        KhachHang khachHangUpdate = khachHangRepository.findById(khachhang.getKhachhangId()).orElseThrow(() -> new DataNotFoundException("Data not found"));

        khachHangUpdate.setTenKhachHang(khachhang.getTenKhachHang());
        khachHangUpdate.setSdt(khachhang.getSdt());
        khachHangUpdate.setDiaChi(khachhang.getDiaChi());
        return khachHangRepository.save(khachHangUpdate);
    }

    @Override
    public KhachHang deleteKhachHang(long KhachHangId,KhachHang khachHang) {
        KhachHang khachHangDelete = khachHangRepository.findById(KhachHangId).orElseThrow(() -> new DataNotFoundException("Data not found"));
        khachHangRepository.delete(khachHangDelete);
        return khachHangDelete;
    }
}
