package com.thuchanh.thuchanhapi.Repository;

import com.thuchanh.thuchanhapi.Entity.KhachHang;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface KhachHangRepository extends JpaRepository<KhachHang, Long> {

    List<KhachHang> findBytenKhachHangContaining(String TenKhach);
}
