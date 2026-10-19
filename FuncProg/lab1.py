import csv

def parse_csv(data: str) -> list[dict]:
    return list(csv.DictReader(data.splitlines()))

def compute_revenue(rows: list[dict]) -> float:
    return sum(map(lambda x:float(x["quantity"]) * float(x["price"]), rows))

def top_item(rows: list[dict]) -> Optional[dict]:
        return next(iter(sorted(rows, key=lambda w: float(w["quantity"]) * float(w["price"]), reverse=True)), None)

if __name__ == "__main__":
    
    theFile = """date,item,quantity,price
    1860-05-02,Pilk,6102.0,1.1
    2020-09-08,Lemon,742.0,2.9
    2014-07-04,Hummus,83.0,4.9
    2023-02-07,Isotope,2.0,20.2
    2026-03-19,Polo,81.0,2.3"""

    emptyFile = ""

    print("Файл:\n", parse_csv(theFile))
    print("\nОбщ. Выручка:", compute_revenue(parse_csv(theFile)))
    print("Строка с макс. выручкой:", top_item(parse_csv(theFile)))
    print("Вывод None ф-цией top_item при отсутствии данных:", top_item(parse_csv(emptyFile)))
