package com.thuchanh.thuchanhapi.Entity;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Entity
@Data
@Table(name = "tbl_khachhang")
@AllArgsConstructor
@NoArgsConstructor
public class KhachHang {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "MaKhach")
    private Long khachhangId;
    @Column(name = "TenKhach")
    private String tenKhachHang;
    @Column(name = "DiajChi")
    private String diaChi;
    @Column(name = "DienThoai")
    private String sdt;
}
