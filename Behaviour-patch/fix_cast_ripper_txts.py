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

def convert_file(src_path, dest_dir):
    """Convert mojibake file to Shift-JIS with CR line endings in destination folder."""
    # Create same folder structure in destination
    rel_path = os.path.relpath(src_path, ".")
    dest_path = os.path.join(dest_dir, rel_path)
    os.makedirs(os.path.dirname(dest_path), exist_ok=True)
    
    with open(src_path, "rb") as f:
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

    # Convert line endings to CR only (Macintosh)
    recovered = recovered.replace('\r\n', '\n')  # CRLF -> LF
    recovered = recovered.replace('\r', '\n')    # CR -> LF
    recovered = recovered.replace('\n', '\r')    # LF -> CR

    # Convert to Shift-JIS and write to destination
    with open(dest_path, "wb") as f:
        f.write(recovered.encode("shift_jis", errors="replace"))

    print(f"Converted: {src_path} -> {dest_path}")



# Confirm before proceeding
print("This script will:")
print("1. Create a 'converted-DATE-TIME' folder")
print("2. Recover from mojibake and convert to Shift-JIS (CR line endings)")
print("3. Leave original files untouched")
confirm = input("Continue? (y/N): ").strip().lower()

if confirm != "y":
    print("Cancelled.")
    exit()

# Create unique converted folder
timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
CONVERTED_DIR = f"converted-{timestamp}"
os.makedirs(CONVERTED_DIR, exist_ok=True)

# Recursive scan
for root, dirs, files in os.walk("."):
    # Skip converted folders
    dirs[:] = [d for d in dirs if not d.startswith("converted-")]
    
    for name in files:
        ext = os.path.splitext(name)[1].lower()
        if ext in VALID_EXT:
            path = os.path.join(root, name)
            convert_file(path, CONVERTED_DIR)

print(f"\nConverted files saved in: {CONVERTED_DIR}")
