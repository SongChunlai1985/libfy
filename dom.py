import os

cur_dir = os.path.dirname(__file__)
# def test():
#     u8_nb_path = os.path.join(cur_dir, 'utf-8_nobom.txt')
#     u8_b_path = os.path.join(cur_dir, 'utf-8_bom.txt')

#     u8_nb = open(u8_nb_path, "rb")
#     u8_b = open(u8_b_path, "rb")

#     print(u8_nb.read(1))
#     print(u8_nb.read(1))
#     print(u8_nb.read(1))
#     print(u8_nb.read(1))
#     print("")
#     print(u8_b.read(1))
#     print(u8_b.read(1))
#     print(u8_b.read(1))
#     print(u8_b.read(1))
#     # efbbbf
#     u8_nb.close()
#     u8_b.close()

def has_bom(content):
    return len(content) >= 3 and content[0] == 0xef \
        and content[1] == 0xbb and content[2] == 0xbf

def to_utf8_bom_f(filename):
    print("To utf8 with bom: " + filename)
    f = open(filename, "rb")
    content = f.read()
    f.close()

    if not has_bom(content):
        f = open(filename, "wb")
        # efbbbf
        bom = bytes([0xef, 0xbb, 0xbf])
        f.write(bom)
        f.write(content)
        f.close()

def to_utf8_bom_d(dir, filters=["h", "cpp", "c", "qml", "qrc"]):
    for root, dirs, files in os.walk(dir):
        for file in files:
            splits = file.split('.')
            if len(splits) >= 2 and splits[-1] in filters:
                to_utf8_bom_f(os.path.join(root, file))

def main():
    src_dir = r"C:/code/fyvisioncheck"       #修改这里
    print("To utf8 with bom: " + src_dir)

    to_utf8_bom_d(src_dir)

#if __name__ == "__main__":
main()
