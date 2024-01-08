from transformers import AutoModelForCausalLM, AutoTokenizer
device = "cuda" # the device to load the model onto

model = AutoModelForCausalLM.from_pretrained("mistralai/Mistral-7B-v0.1")
tokenizer = AutoTokenizer.from_pretrained("mistralai/Mistral-7B-v0.1")

prompt = "Explain the structure and purpose of the following C code:\n int test(int x, int y) { \n\tif(x < y + 10) {\n\t\treturn x;\n\t}\n\treturn y;\n}\n\nint main(int argc, char* argv[]) {\n\ttest(atoi(argv[0]), atoi(argv[1]));\n}\n"

model_inputs = tokenizer([prompt], return_tensors="pt").to(device)
model.to(device)

generated_ids = model.generate(**model_inputs, max_new_tokens=200, do_sample=True)
print(tokenizer.batch_decode(generated_ids)[0])
