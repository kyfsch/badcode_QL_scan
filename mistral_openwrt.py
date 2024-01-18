from transformers import AutoModelForCausalLM, AutoTokenizer
import glob
import torch.cuda

device = "cuda" # the device to load the model onto

model = AutoModelForCausalLM.from_pretrained("mistralai/Mistral-7B-v0.1")
tokenizer = AutoTokenizer.from_pretrained("mistralai/Mistral-7B-v0.1")

questions = []
i = 0

for filename in glob.glob('extracted_functions/openwrt/*.txt'):
    with open(filename, "r") as f:
        func = '\n'.join([x.strip() for x in f.readlines()])

        if len(func) > 2000:
            continue

        questions.append(func + '\n\nThe above function is used to')
        #questions.append(func + '\n\nThe purpose of the above function')
    
    i += 1
    #if i >= 30:
    #    break    

model.to(device)

for quest in questions:
    model_inputs = tokenizer([quest], return_tensors="pt").to(device)

    generated_ids = model.generate(**model_inputs, max_new_tokens=50, do_sample=True)
    result = tokenizer.batch_decode(generated_ids)[0]

    print("\n\n\n\nNEXT\n\n\n\n")
    print(result)
    del model_inputs
    del generated_ids
    del result
    torch.cuda.empty_cache()


