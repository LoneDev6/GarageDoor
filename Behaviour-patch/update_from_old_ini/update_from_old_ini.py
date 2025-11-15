import os
import sys
import datetime
import re

def load_translations(ini_path):
    translations = {}
    with open(ini_path, "r", encoding="shift_jis", errors="ignore") as f:
        for line in f:
            line = line.rstrip("\r\n")
            if "=" in line:
                jp, en = line.split("=", 1)
                # Skip translations containing $ character (bad placeholders)
                if "$" not in jp and "$" not in en:
                    translations[jp] = en
    return translations

def load_fishes(fishes_path):
    """Load fish translations from fishes.ini"""
    fishes = {}
    if not os.path.exists(fishes_path):
        print(f"Warning: {fishes_path} not found, skipping fish translations")
        return fishes
    
    with open(fishes_path, "r", encoding="shift_jis", errors="ignore") as f:
        for line in f:
            line = line.rstrip("\r\n")
            if "=" in line:
                jp, en = line.split("=", 1)
                # Skip translations containing $ character (bad placeholders)
                if "$" not in jp and "$" not in en:
                    fishes[jp] = en
    return fishes

def replace_strings_in_line(line, translations, fishes):
    """Replace Japanese strings in line with English translations"""
    # Combine both translation dictionaries, fishes have priority
    all_translations = {**translations, **fishes}
    
    # Sort by length (longest first) to replace longer strings first
    sorted_translations = sorted(all_translations.items(), key=lambda x: len(x[0]), reverse=True)
    
    for jp, en in sorted_translations:
        # Replace all occurrences of the Japanese string with English
        line = line.replace(jp, en)
    
    return line

def has_japanese(text):
    """Check if text contains Japanese characters"""
    for char in text:
        code = ord(char)
        # Hiragana, Katakana, Kanji ranges
        if (0x3040 <= code <= 0x309F or  # Hiragana
            0x30A0 <= code <= 0x30FF or  # Katakana
            0x4E00 <= code <= 0x9FFF):   # Kanji
            return True
    return False

def process_file(src_path, dst_path, translations, fishes):
    with open(src_path, "r", encoding="shift_jis", errors="ignore", newline="") as f:
        lines = f.readlines()

    out_lines = []
    untranslated = []

    for line in lines:
        # Normalize to CR (\r) only
        raw = line.rstrip("\r\n")

        # Skip certain lines
        if raw.startswith("--") or raw.startswith("#") or raw.startswith("~"):
            out_lines.append(raw + "\r")
            continue
        
        # Skip empty lines
        if not raw:
            out_lines.append(raw + "\r")
            continue
        
        # Skip lines without Japanese characters
        if not has_japanese(raw):
            out_lines.append(raw + "\r")
            continue

        # 1) Exact match
        if raw in translations:
            out_lines.append(translations[raw] + "\r")
            continue

        # 2) Try matching with leading spaces stripped
        stripped = raw.lstrip()
        leading_spaces = raw[:len(raw) - len(stripped)]
        
        if stripped in translations:
            out_lines.append(leading_spaces + translations[stripped] + "\r")
            continue

        # 3) Special: line contains full-width ＠
        if "＠" in stripped:
            stripped_no_at = stripped.replace("＠", "")

            if stripped_no_at in translations:
                # append normal ASCII '@' per tua richiesta
                out_lines.append(leading_spaces + translations[stripped_no_at] + "@" + "\r")
                continue

        # 4) Try precise string replacement for lines with Japanese in them
        if has_japanese(stripped):
            modified = replace_strings_in_line(stripped, translations, fishes)
            if modified != stripped:
                # Found and replaced some Japanese strings
                out_lines.append(leading_spaces + modified + "\r")
                continue

        # No translation found
        out_lines.append(raw + "\r")
        if raw and not raw.startswith("--") and not raw.startswith("#") and not raw.startswith("~"):
            untranslated.append(raw)

    os.makedirs(os.path.dirname(dst_path), exist_ok=True)

    with open(dst_path, "w", encoding="shift_jis", errors="ignore", newline="") as f:
        f.writelines(out_lines)

    return untranslated

def process_folder(src_root, ini_path, fishes_path):
    translations = load_translations(ini_path)
    fishes = load_fishes(fishes_path)

    timestamp = datetime.datetime.now().strftime("%Y%m%d-%H%M%S")
    dst_root = f"modified-{timestamp}"

    all_untranslated = {}

    for root, _, files in os.walk(src_root):
        for file in files:
            if file.lower().endswith(".txt"):
                src_path = os.path.join(root, file)
                rel_path = os.path.relpath(src_path, src_root)
                
                # Skip files in debugger folder
                if "debugger" in rel_path.lower():
                    continue
                
                dst_path = os.path.join(dst_root, rel_path)
                untranslated = process_file(src_path, dst_path, translations, fishes)
                if untranslated:
                    all_untranslated[rel_path] = untranslated

    print("Done. Output folder:", dst_root)
    
    # Save and print untranslated lines
    log_path = os.path.join(dst_root, "untranslated.txt")
    os.makedirs(os.path.dirname(log_path), exist_ok=True)
    
    with open(log_path, "w", encoding="utf-8") as log_file:
        if all_untranslated:
            log_file.write("="*80 + "\n")
            log_file.write("LINEE NON TROVATE NEL TRANSLATION.INI:\n")
            log_file.write("="*80 + "\n")
            
            print("\n" + "="*80)
            print("LINEE NON TROVATE NEL TRANSLATION.INI:")
            print("="*80)
            
            for file_path, lines in all_untranslated.items():
                log_file.write(f"\n[{file_path}]\n")
                print(f"\n[{file_path}]")
                for line in lines:
                    log_file.write(f"  {line}\n")
                    print(f"  {line}")
        else:
            msg = "Tutte le linee sono state trovate nel translation.ini!"
            log_file.write(msg)
            print("\n" + msg)
    
    print(f"\nLog salvato in: {log_path}")


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python update_from_old_ini.py <source_folder> <translation.ini> [fishes.ini]")
        sys.exit(1)

    src_folder = sys.argv[1]
    ini_file = sys.argv[2]
    fishes_file = sys.argv[3] if len(sys.argv) > 3 else "fishes.ini"

    process_folder(src_folder, ini_file, fishes_file)
