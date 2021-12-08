import glob
import win32com.client
import os

# INPUT/OUTPUT PATH
pdfs_path = r"""C:\\Users\\_swet\\Desktop\\"""
output_path = r"""C:\\Users\\_swet\\Desktop"""

word = win32com.client.Dispatch("Word.Application")
word.visible = 0  # CHANGE TO 1 IF YOU WANT TO SEE WORD APPLICATION RUNNING AND ALL MESSAGES OR WARNINGS SHOWN BY WORD
count = 0
print("Trying to convert every docx in Desktop to pdf...")
for i, doc in enumerate(glob.iglob(pdfs_path+"*.docx")):

    # GET FILE NAME AND NORMALIZED PATH
    filename = doc.split('\\')[-1]
    in_file = os.path.abspath(doc)
    print("Converting", filename)
    # CONVERT DOCX TO PDF AND SAVE IT ON THE OUTPUT PATH WITH THE SAME INPUT FILE NAME
    wb = word.Documents.Open(in_file)
    out_file = os.path.abspath(output_path + '\\' + filename[0:-5] + ".pdf")
    wb.SaveAs(out_file, FileFormat=17)
    wb.Close()
    count += 1
print(count, "tasks completed.")
word.Quit()