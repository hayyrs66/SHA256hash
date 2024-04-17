
# User Registration System


This is a simple user registration system implemented in C++ using OpenSSL for password hashing and a hash table to store user data. 


## Instructions for Fedora Linux
1. Clone my repository

```bash
  https://github.com/hayyrs66/SHA256hash
  cd SHA256hash
```

2. Install Crypto++ library and development package:
   ```bash
    sudo dnf install cryptopp cryptopp-devel
    ```

3. Verify installation:
   ```bash
    rpm -qa | grep -i cryptopp

    ```
4. Find the location of sha.h header file:
   ```bash
    rpm -ql cryptopp-devel | grep sha.h

    ```

5. Compile the code:
   ```bash
    g++ main.cpp -lcrypto
    ```

6. Run the executable:
    ```bash
    ./a.out

    ```

## Screenshots

![App Screenshot](/media/hero.png)

