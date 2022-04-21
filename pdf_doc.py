import glob
import win32com.client
import os

# INPUT/OUTPUT PATH
pdfs_path = r"""C:\\Users\\_swet\\Desktop\\"""
output_path = r"""C:\\Users\\_swet\\Desktop"""

word = win32com.client.Dispatch("Word.Application")
word.visible = 0  # CHANGE TO 1 IF YOU WANT TO SEE WORD APPLICATION RUNNING AND ALL MESSAGES OR WARNINGS SHOWN BY WORD
count = 0
folder_in = input("Enter relative input path from desktop : ")
folder_out = input("Enter relative output path from desktop : ")
print("Trying to convert every pdf in Desktop/" + folder_in + " to docx...")
for i, doc in enumerate(glob.iglob(pdfs_path + folder_in + '\\' + "*.pdf")):
    # GET FILE NAME AND NORMALIZED PATH
    filename = doc.split('\\')[-1]
    in_file = os.path.abspath(doc)
    print("Converting", filename)
    # CONVERT PDF TO DOCX AND SAVE IT ON THE OUTPUT PATH WITH THE SAME INPUT FILE NAME
    wb = word.Documents.Open(in_file)
    out_file = os.path.abspath(output_path + '\\' + folder_out + '\\' + filename[0:-4] + ".docx")
    wb.SaveAs2(out_file, FileFormat=16)
    wb.Close()
    count += 1
print(count, "tasks completed.")
word.Quit()
