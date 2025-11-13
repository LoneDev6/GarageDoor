# fix_sjis_cp1252_inverse_backup.py
# Recovers Japanese text from mojibake like "ƒ_ƒ~[F..."
# Also converts UTF-8 to Shift-JIS (SJIS)
# Works recursively on subfolders, creates backups, and overwrites files in place

import os
import shutil
import datetime

# File extensions to process
VALID_EXT = {".txt", ".lng", ".lst", ".scr"}

# Inverse map for CP1252 specials (0x80–0x9F) -> Unicode
inv_cp1252 = {
    0x20AC: 0x80,  # €
    0x201A: 0x82,  # ‚
    0x0192: 0x83,  # ƒ
    0x201E: 0x84,  # „
    0x2026: 0x85,  # …
    0x2020: 0x86,  # †
    0x2021: 0x87,  # ‡
    0x02C6: 0x88,  # ˆ
    0x2030: 0x89,  # ‰
    0x0160: 0x8A,  # Š
    0x2039: 0x8B,  # ‹
    0x0152: 0x8C,  # Œ
    0x017D: 0x8E,  # Ž
    0x2018: 0x91,  # ‘
    0x2019: 0x92,  # ’
    0x201C: 0x93,  # “
    0x201D: 0x94,  # ”
    0x2022: 0x95,  # •
    0x2013: 0x96,  # –
    0x2014: 0x97,  # —
    0x02DC: 0x98,  # ˜
    0x2122: 0x99,  # ™
    0x0161: 0x9A,  # š
    0x203A: 0x9B,  # ›
    0x0153: 0x9C,  # œ
    0x017E: 0x9E,  # ž
    0x0178: 0x9F,  # Ÿ
}

def backup_file(src_path):
    """Copy the file to the backup structure, preserving subfolders."""
    rel_path = os.path.relpath(src_path, ".")
    backup_path = os.path.join(BACKUP_DIR, rel_path)
    os.makedirs(os.path.dirname(backup_path), exist_ok=True)
    shutil.copy2(src_path, backup_path)


def recover_file(path):
    """Convert mojibake file to readable UTF-8."""
    with open(path, "rb") as f:
        data = f.read()

    text = data.decode("utf-8", errors="ignore")

    out_bytes = bytearray()
    for ch in text:
        code = ord(ch)
        if code <= 0xFF:
            out_bytes.append(code)
        else:
            b = inv_cp1252.get(code)
            if b is not None:
                out_bytes.append(b)

    recovered = out_bytes.decode("cp932", errors="ignore")

    with open(path, "w", encoding="utf-8", newline="") as f:
        f.write(recovered)

    print(f"Fixed: {path}")


def convert_utf8_to_sjis(path):
    """Convert UTF-8 encoded file to Shift-JIS (cp932)."""
    try:
        with open(path, "r", encoding="utf-8") as f:
            text = f.read()
        
        with open(path, "w", encoding="cp932") as f:
            f.write(text)
        
        print(f"Converted to SJIS: {path}")
    except Exception as e:
        print(f"Error converting {path}: {e}")


# Confirm before proceeding
print("This script will:")
print("1. Create a backup")
print("2. Recover from mojibake (UTF-8 → Shift-JIS)")
print("3. Convert UTF-8 to Shift-JIS")
confirm = input("Continue? (y/N): ").strip().lower()

if confirm != "y":
    print("Cancelled.")
    exit()

# Create unique backup folder
timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
BACKUP_DIR = f"backup_{timestamp}"
os.makedirs(BACKUP_DIR, exist_ok=True)

# Recursive scan
for root, dirs, files in os.walk("."):
    # Skip backup folders
    dirs[:] = [d for d in dirs if not d.startswith("backup")]
    
    for name in files:
        ext = os.path.splitext(name)[1].lower()
        if ext in VALID_EXT:
            path = os.path.join(root, name)
            backup_file(path)
            recover_file(path)
            convert_utf8_to_sjis(path)

print(f"\nBackup saved in: {BACKUP_DIR}")
