from cryptography.hazmat import backends
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import padding
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes

# code from https://techexpert.tips/pt-br/python-pt-br/python-usando-criptografia-aes/

# AES-256
def encrypt_AES_CBC(data: str, key: bytes, iv: bytes) -> bytes:
    padder = padding.PKCS7(128).padder()
    padded_data = padder.update(data.encode('utf-8'))
    padded_data += padder.finalize()

    cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
    encryptor = cipher.encryptor()
    ciphertext = encryptor.update(padded_data) + encryptor.finalize()
    return ciphertext


def decrypt_AES_CBC(ciphertext: bytes, key: bytes, iv: bytes) -> str:
    decryptor = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend()).decryptor()
    decrypted_data = decryptor.update(ciphertext) + decryptor.finalize()

    unpadder = padding.PKCS7(128).unpadder()
    unpadded_data = unpadder.update(decrypted_data)
    unpadded_data += unpadder.finalize()
    return unpadded_data.decode('utf-8')


# AES 256 needs this length for key and iv
def check_length_key(key: bytes) -> bool:
    return len(key) == 32

def check_length_iv(iv: bytes) -> bool:
    return len(iv) == 16


if __name__ == "__main__":
    # key and iv are in bytes
    key = b'MySuperSecretKey2222222222222222'
    if not check_length_key(key):
        raise ValueError("key must have 32 bytes")
    iv = b'MySuperSecretIV0'
    if not check_length_iv(iv):
        raise ValueError("iv must have 16 bytes")

    plaintext = "My super important message"
    encrypted_text = encrypt_AES_CBC(plaintext, key, iv)
    print(f"Encrypted text: {encrypted_text}")

    decrypted_text = decrypt_AES_CBC(encrypted_text, key, iv)
    print(f"Decrypted text: {decrypted_text}")

