# 第6章 readelf的使用

`readelf` 是一个用于显示 ELF（Executable and Linkable Format）文件信息的工具，通常用于分析和调试可执行文件、共享库、目标文件等。ELF 是 Linux 和其他类 Unix 系统中常用的二进制文件格式。`readelf` 可以帮助开发者查看文件的结构、节（section）、段（segment）、符号表、动态链接信息等。

### 1. 基本用法

`readelf` 的基本用法如下：

```bash
readelf [选项] 文件名
```

### 2. 常用选项

以下是一些常用的 `readelf` 选项：

- `-h` 或 `--file-header`：显示 ELF 文件头信息。
- `-S` 或 `--sections`：显示 ELF 文件的节表（section headers）。
- `-l` 或 `--segments`：显示 ELF 文件的程序头表（program headers）。
- `-s` 或 `--symbols`：显示 ELF 文件的符号表（symbol table）。
- `-d` 或 `--dynamic`：显示 ELF 文件的动态节（dynamic section）。
- `-r` 或 `--relocs`：显示 ELF 文件的重定位表（relocation table）。
- `-x <num>` 或 `--hex-dump=<num>`：以十六进制格式显示指定节的原始内容。
- `-p <num>` 或 `--string-dump=<num>`：以字符串格式显示指定节的原始内容。
- `-V` 或 `--version-info`：显示 ELF 文件的版本信息。
- `-a` 或 `--all`：显示所有信息（相当于同时使用 `-h`, `-l`, `-S`, `-s`, `-r`, `-d`）。

### 3. 示例

#### 3.1 显示 ELF 文件头信息

```bash
readelf -h /path/to/binary
```

输出示例：

```bash
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              DYN (Shared object file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x1060
  Start of program headers:          64 (bytes into file)
  Start of section headers:          14376 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         13
  Size of section headers:           64 (bytes)
  Number of section headers:         30
  Section header string table index: 29
```

#### 3.2 显示节表

```bash
readelf -S /path/to/binary
```

输出示例：

```bash
There are 30 section headers, starting at offset 0x3828:

Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .interp           PROGBITS         0000000000000318  00000318
       000000000000001c  0000000000000000   A       0     0     1
  [ 2] .note.gnu.build-i NOTE             0000000000000338  00000338
       0000000000000024  0000000000000000   A       0     0     4
  ...
```

#### 3.3 显示符号表

```bash
readelf -s /path/to/binary
```

输出示例：

```bash
Symbol table '.dynsym' contains 10 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterTMCloneTable
     2: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND __libc_start_main@GLIBC_2.2.5 (2)
     3: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
     4: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMCloneTable
     5: 0000000000000000     0 FUNC    WEAK   DEFAULT  UND __cxa_finalize@GLIBC_2.2.5 (2)
     6: 0000000000001060     0 FUNC    GLOBAL DEFAULT   14 _start
     7: 0000000000001140     0 FUNC    GLOBAL DEFAULT   14 __libc_csu_init
     8: 00000000000011b0     0 FUNC    GLOBAL DEFAULT   14 __libc_csu_fini
     9: 00000000000011b8     0 FUNC    GLOBAL DEFAULT   14 _fini
```

#### 3.4 显示动态节

```bash
readelf -d /path/to/binary
```

输出示例：

```bash
Dynamic section at offset 0x2e18 contains 25 entries:
  Tag        Type                         Name/Value
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
 0x000000000000000c (INIT)               0x1000
 0x000000000000000d (FINI)               0x11b8
 0x0000000000000019 (INIT_ARRAY)         0x3df8
 0x000000000000001b (INIT_ARRAYSZ)       8 (bytes)
 0x000000000000001a (FINI_ARRAY)         0x3e00
 0x000000000000001c (FINI_ARRAYSZ)       8 (bytes)
 0x000000006ffffef5 (GNU_HASH)           0x3c8
 0x0000000000000005 (STRTAB)             0x4d8
 0x0000000000000006 (SYMTAB)             0x3f8
 0x000000000000000a (STRSZ)              148 (bytes)
 0x000000000000000b (SYMENT)             24 (bytes)
 0x0000000000000015 (DEBUG)              0x0
 0x0000000000000003 (PLTGOT)             0x4000
 0x0000000000000002 (PLTRELSZ)           24 (bytes)
 0x0000000000000014 (PLTREL)             RELA
 0x0000000000000017 (JMPREL)             0x5b8
 0x0000000000000007 (RELA)               0x548
 0x0000000000000008 (RELASZ)             112 (bytes)
 0x0000000000000009 (RELAENT)            24 (bytes)
 0x000000006ffffffe (VERNEED)            0x528
 0x000000006fffffff (VERNEEDNUM)         1
 0x000000006ffffff0 (VERSYM)             0x516
 0x000000006ffffff9 (RELACOUNT)          1
 0x0000000000000000 (NULL)               0x0
```

### 4. 在嵌入式开发中的应用

在嵌入式开发中，`readelf` 是一个非常有用的工具，尤其是在调试和分析嵌入式系统的固件时。以下是一些常见的应用场景：

- **分析固件结构**：通过查看 ELF 文件的节和段，可以了解固件的内存布局、代码段、数据段等信息。
- **符号表分析**：通过查看符号表，可以了解固件中定义的函数、变量等信息，这对于调试和逆向工程非常有用。
- **动态链接分析**：在嵌入式系统中，动态链接库的使用较少，但通过查看动态节，可以了解固件依赖的共享库信息。
- **重定位分析**：在嵌入式系统中，重定位信息对于理解固件的加载过程非常重要。通过查看重定位表，可以了解固件在加载时需要进行的地址调整。

### 5. 总结

`readelf` 是一个功能强大的工具，可以帮助开发者深入了解 ELF 文件的内部结构和内容。在嵌入式开发中，它可以帮助开发者分析固件的结构、调试代码、理解动态链接和重定位等关键问题。熟练掌握 `readelf` 的使用，对于嵌入式开发人员来说是非常有益的。
