let expenses = JSON.parse(localStorage.getItem('expenses')) || [];
let categories = ['food', 'transport', 'entertainment'];
let budget = localStorage.getItem('budget') || 0;

// Add Expense
function addExpense() {
  const amount = document.getElementById('amount').value;
  const category = document.getElementById('category').value;
  const date = document.getElementById('date').value;
  const description = document.getElementById('description').value;

  if (!amount || !date) return alert('Please fill in all fields');

  const expense = { amount, category, date, description };
  expenses.push(expense);
  localStorage.setItem('expenses', JSON.stringify(expenses));
  displayExpenses();
  updateChart();
  updateBudgetProgress();
}

// Display Expenses
function displayExpenses() {
  const tbody = document.querySelector('#expense-table tbody');
  tbody.innerHTML = '';
  let total = 0;

  expenses.forEach((expense, index) => {
    const row = `<tr>
      <td>$${expense.amount}</td>
      <td><i class="fas ${getCategoryIcon(expense.category)}"></i> ${expense.category}</td>
      <td>${expense.date}</td>
      <td>${expense.description}</td>
      <td>
        <button class="edit" onclick="editExpense(${index})"><i class="fas fa-edit"></i></button>
        <button class="delete" onclick="deleteExpense(${index})"><i class="fas fa-trash"></i></button>
      </td>
    </tr>`;
    tbody.innerHTML += row;
    total += parseFloat(expense.amount);
  });

  document.getElementById('total').textContent = total.toFixed(2);
}

// Edit Expense
function editExpense(index) {
  const expense = expenses[index];
  document.getElementById('amount').value = expense.amount;
  document.getElementById('category').value = expense.category;
  document.getElementById('date').value = expense.date;
  document.getElementById('description').value = expense.description;

  expenses.splice(index, 1);
  localStorage.setItem('expenses', JSON.stringify(expenses));
  displayExpenses();
  updateChart();
  updateBudgetProgress();
}

// Delete Expense
function deleteExpense(index) {
  expenses.splice(index, 1);
  localStorage.setItem('expenses', JSON.stringify(expenses));
  displayExpenses();
  updateChart();
  updateBudgetProgress();
}

// Add Category
function addCategory() {
  const newCategory = document.getElementById('new-category').value;
  if (newCategory && !categories.includes(newCategory)) {
    categories.push(newCategory);
    const select = document.getElementById('category');
    select.innerHTML += `<option value="${newCategory}"><i class="fas ${getCategoryIcon(newCategory)}"></i> ${newCategory}</option>`;
  }
}

// Get Category Icon
function getCategoryIcon(category) {
  switch (category) {
    case 'food': return 'fa-utensils';
    case 'transport': return 'fa-bus';
    case 'entertainment': return 'fa-film';
    default: return 'fa-tag';
  }
}

// Set Budget
function setBudget() {
  budget = parseFloat(document.getElementById('budget').value);
  if (isNaN(budget) || budget <= 0) return alert('Please enter a valid budget');
  localStorage.setItem('budget', budget);
  updateBudgetProgress();
}

// Update Budget Progress
function updateBudgetProgress() {
  const total = expenses.reduce((sum, expense) => sum + parseFloat(expense.amount), 0);
  const progressBar = document.getElementById('progress-bar');
  const budgetStatus = document.getElementById('budget-status');

  if (budget > 0) {
    const progress = (total / budget) * 100;
    progressBar.style.width = `${Math.min(progress, 100)}%`;
    budgetStatus.textContent = `Spent: $${total.toFixed(2)} / Budget: $${budget.toFixed(2)}`;
  } else {
    progressBar.style.width = '0%';
    budgetStatus.textContent = 'Budget not set';
  }
}

// Search Expenses
function searchExpenses() {
  const query = document.getElementById('search').value.toLowerCase();
  const filteredExpenses = expenses.filter(expense =>
    expense.description.toLowerCase().includes(query) ||
    expense.category.toLowerCase().includes(query)
  );
  displayFilteredExpenses(filteredExpenses);
}

// Display Filtered Expenses
function displayFilteredExpenses(filteredExpenses) {
  const tbody = document.querySelector('#expense-table tbody');
  tbody.innerHTML = '';
  filteredExpenses.forEach((expense, index) => {
    const row = `<tr>
      <td>$${expense.amount}</td>
      <td><i class="fas ${getCategoryIcon(expense.category)}"></i> ${expense.category}</td>
      <td>${expense.date}</td>
      <td>${expense.description}</td>
      <td>
        <button class="edit" onclick="editExpense(${index})"><i class="fas fa-edit"></i></button>
        <button class="delete" onclick="deleteExpense(${index})"><i class="fas fa-trash"></i></button>
      </td>
    </tr>`;
    tbody.innerHTML += row;
  });
}

// Dark Mode Toggle
document.getElementById('theme-toggle').addEventListener('click', () => {
  document.body.classList.toggle('dark-mode');
  document.getElementById('theme-toggle').innerHTML = document.body.classList.contains('dark-mode') ? '<i class="fas fa-sun"></i>' : '<i class="fas fa-moon"></i>';
});

// Chart.js Integration
const ctx = document.getElementById('expense-chart').getContext('2d');
let chart;

function updateChart() {
  const categoryTotals = {};
  expenses.forEach(expense => {
    categoryTotals[expense.category] = (categoryTotals[expense.category] || 0) + parseFloat(expense.amount);
  });

  if (chart) chart.destroy();
  chart = new Chart(ctx, {
    type: 'pie',
    data: {
      labels: Object.keys(categoryTotals),
      datasets: [{
        data: Object.values(categoryTotals),
        backgroundColor: ['#ff6384', '#36a2eb', '#cc65fe', '#ffce56'],
      }]
    },
    options: {
      responsive: true,
      maintainAspectRatio: false,
    }
  });
}

// Initial Load
displayExpenses();
updateChart();
updateBudgetProgress();