# QTableView

## 表头宽度
## 关于QTableView::setColumnWidth两个坑
## 1. QTableView::setModel要在model的表头数据填充完成后调用，这时候QTableView::setColumnWidth才能生效
 **setModel会调用QHeaderView::initializeSections()，如果这个时候还没有填充表头信息，那么QTableView::setColumnWidth就不会生效**，所以setModel要放在表头设置完后调用。
## 2. QTableView::setColumnWidth要放在QTableView::setModel后调用
## 基本设置
行数，列数，行距，列距

	//设置行距
    verticalHeader()->setDefaultSectionSize(sz);
    verticalHeader()->setMinimumSectionSize(sz);
	//设置列距
    horizontalHeader()->setDefaultSectionSize(sz);
    horizontalHeader()->setMinimumSectionSize(sz);
## 相关样式
### 标题字体，正文字体
## 设置行高
水平线显示，垂直线显示
## 样式
表格背景色，标题栏颜色，边框颜色，边框线条宽度
### 只显示横分割线，不显示竖分割线
思路就是隐藏自带的分割线，设置每个item的下边线的颜色


    setShowGrid(false);// 不显示网格线
    this->setStyleSheet("QTableView{font:italic bold 15px arial;}"
                        "QTableView::item{border:0px solid rgb(255,0,0);}"
                        "QTableView::item{border-bottom:1px solid rgb(255,0,0)}");//边框

### 取消点击一个item时出现的虚线框
	// 不过这样的话，无法使用键盘控制table了.
	setFocusPolicy(Qt::NoFocus);
## 查询功能
## 过滤功能
## 排序功能
- QSortFilterProxyModel
- Custom Sort/Filter Model Example

## 分页功能
## 固定表头
## 固定列
## 多级表头
## 多选功能Checkbox
## 展开行
## 树形数据与懒加载
## 自定义表头
## 表尾合计行
## 合并行或列
## 分页显示功能